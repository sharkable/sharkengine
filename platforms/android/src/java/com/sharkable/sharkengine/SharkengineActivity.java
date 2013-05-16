package com.sharkable.sharkengine;

import android.app.Activity;
import android.content.Context;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageManager;
import android.content.pm.PackageManager.NameNotFoundException;
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
  private int mMeasuredWidth;

  public DemoGLSurfaceView(Context context) {
    super(context);
    mRenderer = new DemoRenderer(context);
    setRenderer(mRenderer);
  }

  @Override
  protected void onMeasure(int widthMeasureSpec, int heightMeasureSpec) {
     mMeasuredWidth = MeasureSpec.getSize(widthMeasureSpec);
     int measuredHeight = MeasureSpec.getSize(heightMeasureSpec);
     this.setMeasuredDimension(mMeasuredWidth, measuredHeight);
     int screenHeight = 640 * measuredHeight / mMeasuredWidth;
     getHolder().setFixedSize(640, screenHeight);
  }

  public boolean onTouchEvent(final MotionEvent event) {
    int index = event.getActionIndex();
    int action = event.getActionMasked();
    String actionString = "Unknown (" + action + ")";
    double x = event.getX() * 640.0 / mMeasuredWidth;
    double y = event.getY() * 640.0 / mMeasuredWidth;
    if (action == MotionEvent.ACTION_DOWN) {
        nativeTouch(0, x, y);
    } else if (action == MotionEvent.ACTION_UP) {
        nativeTouch(1, x, y);
    } else if (action == MotionEvent.ACTION_MOVE) {
        nativeTouch(2, x, y);
    }
    return true;
  }

  private native void nativeTouch(int action, double x, double y);
  private native void nativePause();
}

class DemoRenderer implements GLSurfaceView.Renderer {
  private Context mContext;
  private boolean mDidInit = false;
  private LocalStoreAndroid mLocalStoreJava;

  public DemoRenderer(Context context) {
    mContext = context;
    mLocalStoreJava = new LocalStoreAndroid(context);
  }

  public void onSurfaceCreated(GL10 gl, EGLConfig config) {
  }

  public void onSurfaceChanged(GL10 gl, int w, int h) {
    assert !mDidInit;

    // return apk file path (or null on error)
    String apkFilePath = null;
    ApplicationInfo appInfo = null;
    PackageManager packMgmr = mContext.getPackageManager();
    try {
      appInfo = packMgmr.getApplicationInfo("com.sharkable.sharkengine", 0);
    } catch (NameNotFoundException e) {
      Log.e("Sharkable", "failed to find package");
      e.printStackTrace();
      throw new RuntimeException("Unable to locate assets, aborting...");
    }
    apkFilePath = appInfo.sourceDir;
    nativeInit(mLocalStoreJava, apkFilePath, w, h);
    mDidInit = true;
  }

  public void onDrawFrame(GL10 gl) {
    nativeRender();
  }

  private native void nativeInit(LocalStoreAndroid localStoreJava, String apkPath, int w, int h);
  private native void nativeRender();
  private native void nativeDone();
}
