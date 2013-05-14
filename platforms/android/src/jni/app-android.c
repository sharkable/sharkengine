
#include <jni.h>
#include <sys/time.h>
#include <time.h>
#include <stdint.h>

#include "app.h"
// #include "importgl.h"

#include "libzip/zip.h"

#include "airhockey.h"

int   gAppAlive   = 1;
struct zip* APKArchive;

static int  sWindowWidth  = 320;
static int  sWindowHeight = 960;
static int  sDemoStopped  = 0;
static long sTimeOffset   = 0;
static int  sTimeOffsetInit = 0;
static long sTimeStopped  = 0;

static long
_getTime(void)
{
    struct timeval  now;

    gettimeofday(&now, NULL);
    return (long)(now.tv_sec*1000 + now.tv_usec/1000);
}

static void loadAPK (const char* apkPath) {
  s_log("Loading APK %p !%s!", apkPath, apkPath);
  APKArchive = zip_open(apkPath, 0, NULL);
  if (APKArchive == NULL) {
    s_log("Error loading APK");
    return;
  }

  //Just for debug, print APK contents
//  int numFiles = zip_get_num_files(APKArchive);
//  int i;
//  for (i=0; i<numFiles; i++) {
//    const char* name = zip_get_name(APKArchive, i, 0);
//    if (name == NULL) {
//      s_log("Error reading zip file name at index %i : %s", zip_strerror(APKArchive));
//      return;
//    }
//    s_log("File %i : %s\n", i, name);
//  }
}

/* Call to initialize the graphics state */
JNIEXPORT void JNICALL
Java_com_sharkable_sharkengine_DemoRenderer_nativeInit(JNIEnv * env, jclass cls, jstring apkPath, int w, int h)
{
  s_log("Here in nativeInit()");
  const char* str;
  jboolean isCopy;
  str = (*env)->GetStringUTFChars(env, apkPath, &isCopy);
  s_log("path: %s", str);
  loadAPK(str);

//  importGLInit();
  gAppAlive    = 1;
  sDemoStopped = 0;
  sTimeOffsetInit = 0;
  init(w, h);
}

// JNIEXPORT void JNICALL
// Java_com_sharkable_sharkengine_DemoRenderer_nativeResize( JNIEnv*  env, jobject  thiz, jint w, jint h )
// {
//     sWindowWidth  = w;
//     sWindowHeight = h;
//     setScreenSize(w, h);
//     s_log("resize w=%d h=%d", w, h);
// //    game_engine_->Update();
// }

/* Call to finalize the graphics state */
JNIEXPORT void JNICALL
Java_com_sharkable_sharkengine_DemoRenderer_nativeDone( JNIEnv*  env )
{
//    appDeinit();
//    importGLDeinit();
}

JNIEXPORT void JNICALL
Java_com_sharkable_sharkengine_DemoGLSurfaceView_nativeTouch( JNIEnv*  env, jobject  thiz, jint action, jdouble x, jdouble y)
{
  s_log("touch: %d %f,%f", action, x, y);
  touch(action, x, y);
}

/* This is called to indicate to the render loop that it should
 * stop as soon as possible.
 */
JNIEXPORT void JNICALL
Java_com_sharkable_sharkengine_DemoGLSurfaceView_nativePause( JNIEnv*  env )
{
    sDemoStopped = !sDemoStopped;
    if (sDemoStopped) {
        /* we paused the animation, so store the current
         * time in sTimeStopped for future nativeRender calls */
        sTimeStopped = _getTime();
    } else {
        /* we resumed the animation, so adjust the time offset
         * to take care of the pause interval. */
        sTimeOffset -= _getTime() - sTimeStopped;
    }
}

/* Call to render the next GL frame */
JNIEXPORT void JNICALL
Java_com_sharkable_sharkengine_DemoRenderer_nativeRender( JNIEnv*  env )
{
    long   curTime;

    /* NOTE: if sDemoStopped is TRUE, then we re-render the same frame
     *       on each iteration.
     */
    if (sDemoStopped) {
        curTime = sTimeStopped + sTimeOffset;
    } else {
        curTime = _getTime() + sTimeOffset;
        if (sTimeOffsetInit == 0) {
            sTimeOffsetInit = 1;
            sTimeOffset     = -curTime;
            curTime         = 0;
        }
    }

    //s_log("nativeRender: curTime=%ld", curTime);

    update();
    //appRender(curTime, sWindowWidth, sWindowHeight);
}
