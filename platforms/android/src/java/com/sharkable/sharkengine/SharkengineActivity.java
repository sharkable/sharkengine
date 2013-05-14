package com.sharkable.sharkengine;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

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

public class SharkengineActivity extends Activity {
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

    private GLSurfaceView mGLView;

    static {
        System.loadLibrary("sharkengine");
    }
}

class DemoGLSurfaceView extends GLSurfaceView {
    public DemoGLSurfaceView(Context context) {
        super(context);
        mRenderer = new DemoRenderer(context);
        setRenderer(mRenderer);
    }
    
    @Override
    protected void onMeasure(int widthMeasureSpec, int heightMeasureSpec) {
       mParentWidth = MeasureSpec.getSize(widthMeasureSpec);
       mParentHeight = MeasureSpec.getSize(heightMeasureSpec);
       Log.d("Sharkable", "onMeasure: " + mParentWidth + "," + mParentHeight);
       this.setMeasuredDimension(mParentWidth, mParentHeight);
       int screenHeight = 640 * mParentHeight / mParentWidth;
       getHolder().setFixedSize(640, 640 * mParentHeight / mParentWidth);
    }

    public boolean onTouchEvent(final MotionEvent event) {
        Log.d("Sharkable", "measured size: " + getMeasuredWidth() + "," + getMeasuredHeight());
        int index = event.getActionIndex();
        int action = event.getActionMasked();
        String actionString = "Unknown (" + action + ")";
        double x = event.getX() * 640.0 / mParentWidth;
        double y = event.getY() * 640.0 / mParentWidth;
        if (action == MotionEvent.ACTION_DOWN) {
            actionString = "DOWN";
            nativeTouch(0, x, y);
        } else if (action == MotionEvent.ACTION_UP) {
            actionString = "UP";
            nativeTouch(1, x, y);
        } else if (action == MotionEvent.ACTION_MOVE) {
            actionString = "MOVE";
            nativeTouch(2, x, y);
        }
//        Log.d("Sharkable", "pointed " + event.getPointerId(index) + " " + event.getX(index) + "," + event.getY(index)
//             + " " + actionString);
        return true;
    }

    DemoRenderer mRenderer;
    int mParentWidth;
    int mParentHeight;

    private static native void nativeTouch(int action, double x, double y);
    private static native void nativePause();
}

class DemoRenderer implements GLSurfaceView.Renderer {
    Context context;
    boolean mDidInit = false;

    public DemoRenderer(Context context) {
      this.context = context;
    }

    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
    }

    public void onSurfaceChanged(GL10 gl, int w, int h) {
        Log.d("Sharkable", "SurfaceChanged: " + w + "," + h);
        assert !mDidInit;
  
        // return apk file path (or null on error)
        String apkFilePath = null;
        ApplicationInfo appInfo = null;
        PackageManager packMgmr = context.getPackageManager();
        try {
            appInfo = packMgmr.getApplicationInfo("com.sharkable.sharkengine", 0);
        } catch (NameNotFoundException e) {
            Log.d("Sharkable", "failed to find package");
            e.printStackTrace();
            throw new RuntimeException("Unable to locate assets, aborting...");
        }
        apkFilePath = appInfo.sourceDir;
        Log.d("Sharkable", "before nativeInit() path: " + apkFilePath);
        nativeInit(apkFilePath, w, h);
        mDidInit = true;
        Log.d("Sharkable", "after nativeInit()");
    }

    public void onDrawFrame(GL10 gl) {
        nativeRender();
    }
    
    private static native void nativeInit(String apkPath, int w, int h);
    private static native void nativeRender();
    private static native void nativeDone();
}
