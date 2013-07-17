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

import com.sharkable.sharkengine.modules.AdEngineAndroid;
import com.sharkable.sharkengine.modules.LocalStoreAndroid;

public class SharkengineActivity extends Activity {
  private GLSurfaceView mGLView;

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
}

class DemoGLSurfaceView extends GLSurfaceView {
  private DemoRenderer mRenderer;
  private int mScreenPixelWidth;
  private int mGameRenderWidth;

  public DemoGLSurfaceView(Activity activity) {
    super(activity);
    // TODO I need a solution for Gingerbread. Otherwise it loses textures.
    if (android.os.Build.VERSION.SDK_INT >= android.os.Build.VERSION_CODES.HONEYCOMB) {
      setPreserveEGLContextOnPause(true);
    }
    mRenderer = new DemoRenderer(activity);
    setRenderer(mRenderer);
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

  private native void nativeTouch(int touchId, int action, double x, double y);
  private native void nativePause();
}

class DemoRenderer implements GLSurfaceView.Renderer {
  private Activity mActivity;
  private boolean mDidInit = false;
  private AdEngineAndroid mAdEngine;
  private LocalStoreAndroid mLocalStore;

  public DemoRenderer(Activity activity) {
    mActivity = activity;
    mAdEngine = new AdEngineAndroid(activity);
    mLocalStore = new LocalStoreAndroid(activity);
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

    // return apk file path (or null on error)
    String apkFilePath = null;
    ApplicationInfo appInfo = null;
    PackageManager packMgmr = mActivity.getPackageManager();
    try {
      appInfo = packMgmr.getApplicationInfo("com.sharkable.sharkengine", 0);
    } catch (NameNotFoundException e) {
      Log.e("Sharkable", "failed to find package");
      e.printStackTrace();
      throw new RuntimeException("Unable to locate assets, aborting...");
    }
    apkFilePath = appInfo.sourceDir;
    nativeInit(mAdEngine, mLocalStore, mActivity.getAssets(), apkFilePath, w, h);
    mDidInit = true;
  }

  public void onDrawFrame(GL10 gl) {
    synchronized (this) {
      nativeRender();
    }
  }

  private native void nativeInit(AdEngineAndroid adEngineJava, LocalStoreAndroid localStoreJava,
                                 AssetManager assetManager, String apkPath, int w, int h);
  private native void nativeReloadTextures();
  private native void nativeRender();
}
