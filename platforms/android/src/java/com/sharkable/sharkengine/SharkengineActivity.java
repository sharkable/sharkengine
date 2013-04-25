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


import java.util.logging.Level;
import java.util.logging.Logger;

public class SharkengineActivity extends Activity {
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
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

    public boolean onTouchEvent(final MotionEvent event) {
        int index = event.getActionIndex();
        int action = event.getActionMasked();
        String actionString = "Unknown (" + action + ")";
        if (action == MotionEvent.ACTION_DOWN) {
            actionString = "DOWN";
            nativeTouch(0, event.getX(), event.getY());
        } else if (action == MotionEvent.ACTION_UP) {
            actionString = "UP";
            nativeTouch(1, event.getX(), event.getY());
        } else if (action == MotionEvent.ACTION_MOVE) {
            actionString = "MOVE";
            nativeTouch(2, event.getX(), event.getY());
        }
//        Log.d("Sharkable", "pointed " + event.getPointerId(index) + " " + event.getX(index) + "," + event.getY(index)
//             + " " + actionString);
        return true;
    }

    DemoRenderer mRenderer;

    private static native void nativeTouch(int action, double x, double y);
    private static native void nativePause();
}

class DemoRenderer implements GLSurfaceView.Renderer {
    Context context;

    public DemoRenderer(Context context) {
      this.context = context;
    }

    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
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
        nativeInit(apkFilePath);
        Log.d("Sharkable", "after nativeInit()");
    }

    public void onSurfaceChanged(GL10 gl, int w, int h) {
        //gl.glViewport(0, 0, w, h);
        nativeResize(w, h);
    }

    public void onDrawFrame(GL10 gl) {
        nativeRender();
    }

    private static native void nativeInit(String apkPath);
    private static native void nativeResize(int w, int h);
    private static native void nativeRender();
    private static native void nativeDone();
}
