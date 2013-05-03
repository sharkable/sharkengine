//
//  game_engine.h
//  GameEngine
//
//  Created by Jon Sharkey on 2010-04-10.
//  Copyright 2010 Sharkable. All rights reserved.
//

#ifndef GAMEENGINE_GAMEENGINE_H_
#define GAMEENGINE_GAMEENGINE_H_

#include <vector>

#include "gameengine/coordinate_types.h"
#include "gameengine/positions.h"
#include "gameengine/resource_loader.h"
#include "gameengine/touch.h"

typedef enum {
  kPlatformTypePhone = 0,
  kPlatformTypeTablet
} PlatformType;

typedef enum {
  kPlatformResolutionLow = 0,
  kPlatformResolutionHigh
} PlatformResolution;

class AdEngine;
class AnalyticsEngine;
class AppStoreEngine;
class AssetReader;
class EngineView;
class GameEngine;
class GameEngineFactory;

extern "C" {
  void sharkengine_init(sp<GameEngine> game_engine);
}

class GameEngine {
 public:
  GameEngine();

  // TODO consider refactoring this information exposure for game vs. platform, using inheritance.
  void SetScreenSize(ScreenSize screen_size);
  void SetGameSize(GameSize game_size);
  void SetScreenOffset(ScreenPoint screen_offset);

  void Update();
  void Render();
  void ClearTouches();

  void PushView(sp<EngineView> view);
  void PopView();
  void RemoveView(EngineView *view);
  void SetRootView(sp<EngineView> view);

  PlatformType platform_type() { return platform_type_; }
  void set_platform_type(PlatformType platform_type) { platform_type_ = platform_type; };

  PlatformResolution platform_resolution() { return platform_resolution_; }
  void set_platform_resolution(PlatformResolution platform_resolution) {
    platform_resolution_ = platform_resolution;
  };

  sp<GameEngineFactory> factory() { return factory_; }
  void set_factory(sp<GameEngineFactory> factory) { factory_ = factory; }

  sp<AdEngine> ad_engine() { return ad_engine_; }
  void set_ad_engine(sp<AdEngine> ad_engine) { ad_engine_ = ad_engine; }

  sp<AnalyticsEngine> analytics_engine() { return analytics_engine_; }
  void set_analytics_engine(sp<AnalyticsEngine> analytics_engine) {
    analytics_engine_ = analytics_engine;
  }

  sp<AppStoreEngine> app_store_engine() { return app_store_engine_; }
  void set_app_store_engine(sp<AppStoreEngine> app_store_engine) {
    app_store_engine_ = app_store_engine;
  }

  ResourceLoader &resource_loader() { return resource_loader_; }

  void load_positions(AssetReader &file) { positions_->LoadFile(file); }
  GamePoint position(std::string name) { return positions_->position(name); }

  void set_touches_began(std::vector<Touch> touches_began) { touches_began_ = touches_began; }
  void set_touches_moved(std::vector<Touch> touches_moved) { touches_moved_ = touches_moved; }
  void set_touches_ended(std::vector<Touch> touches_ended) { touches_ended_ = touches_ended; }

  ScreenSize screen_size() { return screen_size_; }
  GameSize game_size() { return game_size_; }

  ScreenSize game_size_to_screen_size(GameSize game_size_) {
    return screen_size_make(game_size_.width * game_to_screen_point_ratio_x_,
                            game_size_.height * game_to_screen_point_ratio_y_);
  }
  ScreenPoint game_point_to_screen_point(GamePoint game_point_) {
    return screen_point_make(game_point_.x * game_to_screen_point_ratio_x_ + screen_offset_.x,
                             game_point_.y * game_to_screen_point_ratio_y_ + screen_offset_.y);
  }
  GameSize screen_size_to_game_size(ScreenSize screen_size_) {
    return game_size_make(screen_size_.width * screen_to_game_point_ratio_x_,
                          screen_size_.height * screen_to_game_point_ratio_y_);
  }
  GamePoint screen_point_to_game_point(ScreenPoint screen_point_) {
    return game_point_make((screen_point_.x - screen_offset_.x) * screen_to_game_point_ratio_x_,
                           (screen_point_.y - screen_offset_.y) * screen_to_game_point_ratio_y_);
  }

 private:
  void UpdateSizeRatios();

  PlatformType platform_type_;
  PlatformResolution platform_resolution_;

  // Platform specific
  sp<GameEngineFactory> factory_;
  sp<AdEngine> ad_engine_;
  sp<AnalyticsEngine> analytics_engine_;
  sp<AppStoreEngine> app_store_engine_;

  ResourceLoader resource_loader_;
  sp<Positions> positions_;
  std::vector<sp<EngineView> > views_;
  std::vector<sp<EngineView> > next_views_;
  std::vector<Touch> touches_began_;
  std::vector<Touch> touches_moved_;
  std::vector<Touch> touches_ended_;
  ScreenSize screen_size_;
  GameSize game_size_;
  ScreenPoint screen_offset_;
  double game_to_screen_point_ratio_x_;
  double game_to_screen_point_ratio_y_;
  double screen_to_game_point_ratio_x_;
  double screen_to_game_point_ratio_y_;
};

#endif
