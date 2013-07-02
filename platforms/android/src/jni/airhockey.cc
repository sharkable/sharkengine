
#include <jni.h>


extern "C" {
  void init(JNIEnv *env, jobject ad_engine_java, jobject local_store_java, jobject asset_manager,
            int width, int height);
  void update();
  void touch(int touch_id, int action, double x, double y);
}


#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include <GLES/gl.h>

#include "gameengine/android/modules/ad_engine_android.h"
#include "gameengine/android/modules/analytics_engine_android.h"
#include "gameengine/android/modules/game_engine_factory_android.h"
#include "gameengine/android/modules/local_store_android.h"
#include "gameengine/game_engine.h"
#include "gameengine/game_engine.h"
#include "soundengine/sound_player.h"


static sp<GameEngine> game_engine_;

void init(JNIEnv *env, jobject ad_engine_java, jobject local_store_java, jobject asset_manager,
          int width, int height) {
  glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
  glDepthMask(false);
  glEnable(GL_CULL_FACE);
  glEnable(GL_BLEND);
  glEnable(GL_TEXTURE_2D);
  glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);

  // TODO This shouldn't be hardcoded. Rethink this anyways.

  game_engine_.reset(new GameEngine());

  Texture2D::SetScreenHeight(height);
  game_engine_->set_screen_size(screen_size_make(width, height));

  game_engine_->set_platform_type(kPlatformTypePhone);
  game_engine_->set_platform_resolution(kPlatformResolutionHigh);

  sp<GameEngineFactory> factory = sp<GameEngineFactory>(new GameEngineFactoryAndroid());
  game_engine_->set_factory(factory);

  sp<LocalStore> local_store = sp<LocalStore>(new LocalStoreAndroid(env, local_store_java));
  game_engine_->set_local_store(local_store);

  sp<AdEngine> ad_engine = sp<AdEngine>(new AdEngineAndroid(env, ad_engine_java));
  game_engine_->set_ad_engine(ad_engine);

  sp<AnalyticsEngine> analytics_engine = sp<AnalyticsEngine>(new AnalyticsEngineAndroid(env));
  game_engine_->set_analytics_engine(analytics_engine);

  AAssetManager *mgr = AAssetManager_fromJava(env, asset_manager);
  assert(NULL != mgr);
  // TODO casting is bad
  ((SoundPlayerImpl *)SoundPlayer::instance())->setAssetManager(mgr);

  sharkengine_init(game_engine_);
}

void update() {
  game_engine_->Update();

    int backingWidth_ = 640;
    int backingHeight_ = 1138;

    glViewport(0, 0, backingWidth_, backingHeight_);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrthof(0, backingWidth_, 0, backingHeight_, -1, 1);

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
