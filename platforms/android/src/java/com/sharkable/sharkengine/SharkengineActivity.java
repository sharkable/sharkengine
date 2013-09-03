package com.sharkable.sharkengine;

import android.app.Activity;
import android.content.Context;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageManager;
import android.content.pm.PackageManager.NameNotFoundException;
import android.content.res.AssetManager;
import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.util.Log;
import android.view.MotionEvent;
import android.view.Window;
import android.view.WindowManager;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import com.flurry.android.FlurryAgent;
import com.google.ads.Ad;

import com.sharkable.sharkengine.modules.AndroidAdModule;
import com.sharkable.sharkengine.modules.AppStoreEngineAndroid;
import com.sharkable.sharkengine.modules.LocalStoreAndroid;

public class SharkengineActivity extends Activity {
  private DemoGLSurfaceView mGLView;

  static {
      System.loadLibrary("sharkengine");
  }

  @Override
  protected void onCreate(Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);

    requestWindowFeature(Window.FEATURE_NO_TITLE);
    getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,
                         WindowManager.LayoutParams.FLAG_FULLSCREEN);
    mGLView = new DemoGLSurfaceView(this);

    setContentView(mGLView);
  }

  @Override
  protected void onStart() {
    super.onStart();
    // TODO the key should not be here.
    FlurryAgent.onStartSession(this, "S3C3R982GNCVFY2W77GQ");
  }

  @Override
  protected void onStop() {
    super.onStop();
    FlurryAgent.onEndSession(this);
  }

  @Override
  protected void onPause() {
    super.onPause();
    mGLView.onPause();
  }

  @Override
  protected void onResume() {
    super.onResume();
    mGLView.onResume();
  }

  @Override
  public void onBackPressed() {
    mGLView.onBackPressed();
  }

  public void ignoreNextPause() {
    mGLView.ignoreNextPause();
  }
}

class DemoGLSurfaceView extends GLSurfaceView {
  private DemoRenderer mRenderer;
  private int mScreenPixelWidth;
  private int mGameRenderWidth;
  private boolean mIgnoreNextPause = false;

  public DemoGLSurfaceView(SharkengineActivity activity) {
    super(activity);
    // TODO I need a solution for Gingerbread. Otherwise it loses textures.
    if (android.os.Build.VERSION.SDK_INT >= android.os.Build.VERSION_CODES.HONEYCOMB) {
      setPreserveEGLContextOnPause(true);
    }
    mRenderer = new DemoRenderer(activity);
    setRenderer(mRenderer);
  }

  @Override
  public void onPause() {
    super.onPause();
    if (mIgnoreNextPause) {
      mIgnoreNextPause = false;
    } else {
      mRenderer.pause();
    }
  }

  @Override
  protected void onMeasure(int widthMeasureSpec, int heightMeasureSpec) {
    mScreenPixelWidth = MeasureSpec.getSize(widthMeasureSpec);
    int screenPixelHeight = MeasureSpec.getSize(heightMeasureSpec);
    this.setMeasuredDimension(mScreenPixelWidth, screenPixelHeight);
    mGameRenderWidth = (mScreenPixelWidth >= 640) ? 640 : 320;
    int screenHeight = mGameRenderWidth * screenPixelHeight / mScreenPixelWidth;
    getHolder().setFixedSize(mGameRenderWidth, screenHeight);
  }

  public boolean onTouchEvent(final MotionEvent event) {
    synchronized (mRenderer) {
      int action = event.getActionMasked();

      if (action == MotionEvent.ACTION_MOVE) {
        for (int i = 0; i < event.getPointerCount(); i++) {
          int id = event.getPointerId(i);
          double x = event.getX(i) * mGameRenderWidth / mScreenPixelWidth;
          double y = event.getY(i) * mGameRenderWidth / mScreenPixelWidth;
          nativeTouch(id, 2, x, y);
        }
      } else {
        int index = event.getActionIndex();
        int id = event.getPointerId(index);
        double x = event.getX(index) * mGameRenderWidth / mScreenPixelWidth;
        double y = event.getY(index) * mGameRenderWidth / mScreenPixelWidth;
        if (action == MotionEvent.ACTION_DOWN || action == MotionEvent.ACTION_POINTER_DOWN) {
          nativeTouch(id, 0, x, y);
        } else if (action == MotionEvent.ACTION_UP || action == MotionEvent.ACTION_POINTER_UP) {
          nativeTouch(id, 1, x, y);
        }
      }
      return true;
    }
  }

  public void onBackPressed() {
    mRenderer.onBackPressed();
  }

  public void ignoreNextPause() {
    mIgnoreNextPause = true;
  }

  private native void nativeTouch(int touchId, int action, double x, double y);
}

class DemoRenderer implements GLSurfaceView.Renderer {
  private SharkengineActivity mActivity;
  private boolean mDidInit = false;
  private boolean mPauseOnNextFrame = false;
  private boolean mHandleBackOnNextFrame = false;
  private boolean mQuitOnNextFrame = false;
  // TODO make names consistent. Engine? Not engine? Also variables everywhere.
  private AndroidAdModule mAdModule;
  private LocalStoreAndroid mLocalStore;
  private AppStoreEngineAndroid mAppStoreEngine;

  public DemoRenderer(SharkengineActivity activity) {
    mActivity = activity;
    mAdModule = new AndroidAdModule(activity);
    mLocalStore = new LocalStoreAndroid(activity);
    mAppStoreEngine = new AppStoreEngineAndroid(activity);
  }

  public void onSurfaceCreated(GL10 gl, EGLConfig config) {
    if (mDidInit) {
      nativeReloadTextures();
    }
  }

  public void onSurfaceChanged(GL10 gl, int w, int h) {
    if (mDidInit) {
      return;
    }
    mDidInit = true;

    // return apk file path (or null on error)
    String apkFilePath = null;
    ApplicationInfo appInfo = null;
    PackageManager packMgmr = mActivity.getPackageManager();
    try {
      // TODO make this generic. Maybe take it in the constructor from the subclass of
      // SharkengineActivity.
      appInfo = packMgmr.getApplicationInfo("com.sharkable.airhockey", 0);
    } catch (NameNotFoundException e) {
      Log.e("Sharkable", "failed to find package");
      e.printStackTrace();
      throw new RuntimeException("Unable to locate assets, aborting...");
    }
    apkFilePath = appInfo.sourceDir;
    nativeInit(mAdModule, mLocalStore, mAppStoreEngine, mActivity.getAssets(), apkFilePath, w, h);
  }

  public void onDrawFrame(GL10 gl) {
    synchronized (this) {
      if (mPauseOnNextFrame) {
        nativePause();
        mPauseOnNextFrame = false;
      }
      if (mHandleBackOnNextFrame) {
        if (!nativeHandleBackButton()) {
          quit();
        }
        mHandleBackOnNextFrame = false;
      }
      nativeRender();
      if (mQuitOnNextFrame) {
        nativeShutdown();
        mActivity.finish();
      }
    }
  }

  public void onBackPressed() {
    mHandleBackOnNextFrame = true;
  }

  public void pause() {
    mPauseOnNextFrame = true;
  }

  public void quit() {
    mQuitOnNextFrame = true;
  }

  private native void nativeInit(AndroidAdModule adModuleJava, LocalStoreAndroid localStoreJava,
                                 AppStoreEngineAndroid appStoreJava, AssetManager assetManager,
                                 String apkPath, int w, int h);
  private native void nativeShutdown();
  private native void nativePause();
  private native boolean nativeHandleBackButton();
  private native void nativeReloadTextures();
  private native void nativeRender();
}
