
#include <jni.h>
#include <sys/time.h>
#include <time.h>
#include <stdint.h>

#include "app.h"

#include "libzip/zip.h"

#include "airhockey.h"

struct zip *APKArchive;

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

// Just for debug, print APK contents
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

JNIEXPORT void JNICALL
Java_com_sharkable_sharkengine_DemoGLSurfaceView_nativeTouch(JNIEnv *env, jobject thiz,
                                                             jint touch_id, jint action, jdouble x,
                                                             jdouble y) {
  touch(touch_id, action, x, y);
}

/* Call to initialize the graphics state */
JNIEXPORT void JNICALL
Java_com_sharkable_sharkengine_DemoRenderer_nativeInit(JNIEnv *env, jobject thiz,
                                                       jobject ad_engine_java,
                                                       jobject local_store_java,
                                                       jobject asset_manager, jstring apkPath,
                                                       int w, int h) {
  s_log("Here in nativeInit()");
  const char *str;
  jboolean isCopy;
  str = (*env)->GetStringUTFChars(env, apkPath, &isCopy);
  s_log("path: %s", str);
  loadAPK(str);
  (*env)->ReleaseStringUTFChars(env, apkPath, str);

  init(env, ad_engine_java, local_store_java, asset_manager, w, h);  
}

JNIEXPORT void JNICALL
Java_com_sharkable_sharkengine_DemoRenderer_nativePause(JNIEnv *env, jobject thiz) {
  notify_pause();
}

Java_com_sharkable_sharkengine_DemoRenderer_nativeReloadTextures(JNIEnv *env, jobject thiz) {
  reload_textures();
}

JNIEXPORT void JNICALL
Java_com_sharkable_sharkengine_DemoRenderer_nativeRender(JNIEnv *env, jobject thiz) {
  update();
}
