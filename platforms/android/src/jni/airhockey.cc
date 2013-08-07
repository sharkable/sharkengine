
#include <jni.h>


extern "C" {
  void setupOpengl();
  void init(JNIEnv *env, jobject ad_engine_java, jobject local_store_java, jobject app_store_java,
            jobject asset_manager, int width, int height);
  void shutdown();
  int handle_back_button();
  void reload_textures();
  void notify_pause();
  void update();
  void touch(int touch_id, int action, double x, double y);
}


#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include <GLES/gl.h>

#include "gameengine/android/modules/android_ad_engine.h"
#include "gameengine/android/modules/android_analytics_engine.h"
#include "gameengine/android/modules/android_app_store_engine.h"
#include "gameengine/android/modules/android_game_engine_factory.h"
#include "gameengine/android/modules/android_local_store.h"
#include "gameengine/game_engine.h"
#include "gameengine/game_engine.h"
#include "soundengine/sound_player.h"


static sp<GameEngine> game_engine_;

int backing_width__;
int backing_height__;

void setup_opengl() {
  glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
  glDepthMask(false);
  glEnable(GL_CULL_FACE);
  glEnable(GL_BLEND);
  glEnable(GL_TEXTURE_2D);
  glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);
}

void init(JNIEnv *env, jobject ad_engine_java, jobject local_store_java, jobject app_store_java,
          jobject asset_manager, int width, int height) {
  setup_opengl();

  backing_width__ = width;
  backing_height__ = height;

  game_engine_.reset(new GameEngine());

  Texture2D::SetScreenHeight(height);
  game_engine_->set_screen_size(screen_size_make(width, height));

  game_engine_->set_platform_type(kPlatformTypePhone);
  game_engine_->set_platform_resolution(
      width >= 640 ? kPlatformResolutionHigh : kPlatformResolutionLow);

  sp<GameEngineFactory> factory = sp<GameEngineFactory>(new AndroidGameEngineFactory());
  game_engine_->set_factory(factory);

  sp<LocalStore> local_store = sp<LocalStore>(new AndroidLocalStore(env, local_store_java));
  game_engine_->set_local_store(local_store);

  sp<AdEngine> ad_engine = sp<AdEngine>(new AndroidAdEngine(env, ad_engine_java));
  game_engine_->set_ad_engine(ad_engine);

  sp<AppStoreEngine> app_store_engine =
      sp<AppStoreEngine>(new AndroidAppStoreEngine(env, app_store_java));
  game_engine_->set_app_store_engine(app_store_engine);

  sp<AnalyticsEngine> analytics_engine = sp<AnalyticsEngine>(new AndroidAnalyticsEngine(env));
  game_engine_->set_analytics_engine(analytics_engine);

  AAssetManager *mgr = AAssetManager_fromJava(env, asset_manager);
  assert(NULL != mgr);
  // TODO casting is bad
  ((SoundPlayerImpl *)SoundPlayer::instance())->setAssetManager(mgr);

  sharkengine_init(game_engine_.get());
}

void shutdown() {
  game_engine_.reset();
  SoundPlayer::shutdown();  // TODO SoundEngine should be an instance in GameEngine. singleton bad.
}

int handle_back_button() {
  return game_engine_->HandleBackButton();
}

void reload_textures() {
  setup_opengl();
  game_engine_->resource_loader().ReloadTextures();
}

void notify_pause() {
  game_engine_->NotifyPause();
}

void update() {
  game_engine_->Update();

  glViewport(0, 0, backing_width__, backing_height__);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrthof(0, backing_width__, 0, backing_height__, -1, 1);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  game_engine_->Render();
}

#include "gameengine/touch.h"
#include <vector>
using std::vector;

void touch(int touch_id, int action, double x, double y) {
  Touch touch;
  touch.set_location(game_engine_->screen_point_to_game_point(screen_point_make(x, y)));
  touch.set_identifier((void *)(touch_id + 100));  // We don't want NULL identifiers, so add 100.
  if (action == 0) {
    game_engine_->AddTouchBegan(touch);
  } else if (action == 1) {
    game_engine_->AddTouchEnded(touch);
  } else if (action == 2) {
    game_engine_->AddTouchMoved(touch);
  }
}
