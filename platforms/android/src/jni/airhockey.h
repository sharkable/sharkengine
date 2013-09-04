#ifndef AIRHOCKEY_H_
#define AIRHOCKEY_H_

#ifdef __cplusplus
extern "C" {
#endif

void init(JNIEnv *env, jobject ad_module_java, jobject persistence_module_java,
          jobject app_store_module_java, jobject asset_manager, int width, int height);
void shutdown();
int handle_back_button();
void reload_textures();
void pause();
void update();
void touch(int touch_id, int action, double x, double y);

#ifdef __cplusplus
}
#endif

#endif
