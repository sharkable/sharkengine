#ifndef AIRHOCKEY_H_
#define AIRHOCKEY_H_

#ifdef __cplusplus
extern "C" {
#endif

void init(JNIEnv *env, jobject ad_engine_java, jobject local_store_java, jobject asset_manager,
          int width, int height);
void update();
void touch(int touch_id, int action, double x, double y);

#ifdef __cplusplus
}
#endif

#endif
