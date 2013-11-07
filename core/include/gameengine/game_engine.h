//
//  game_engine.h
//  GameEngine
//
//  Created by Jon Sharkey on 2010-04-10.
//  Copyright 2010 Sharkable. All rights reserved.
//

#ifndef GAMEENGINE_GAMEENGINE_H_
#define GAMEENGINE_GAMEENGINE_H_

#include <utility>
#include <vector>

#include "gameengine/coordinate_types.h"
#include "gameengine/engine_view.h"
#include "gameengine/platform.h"
#include "gameengine/positions.h"
#include "gameengine/resource_loader.h"
#include "gameengine/touch.h"
#include "gameengine/datastructures/staged_vector.h"

class AdModule;
class AnalyticsModule;
class AppStoreModule;
class AssetReader;
class AssetReaderFactoryModule;
class GameEngine;
class InputModule;
class Label;
class PersistenceModule;
namespace SharkSound {
  class SoundController;
}

extern "C" {
  void sharkengine_init(GameEngine &game_engine);
}

class GameEngine {
 public:
  GameEngine();

  // Platform functions
  // Don't call these from an app.
  void Update();
  void Render();
  void NotifyPause();
  void ClearTouches();
  void AddTouchBegan(Touch touch);
  void AddTouchMoved(Touch touch);
  void AddTouchEnded(Touch touch);
  void AddKeyPressed(int key);
  void AddMouseDelta(float delta_x, float delta_y);
  bool HandleBackButton();
  void HandlePauseButton();

  // App functions
  void PushView(EngineView *view);
  void PopView();
  void RemoveView(EngineView *view);
  void SetRootView(EngineView *view);
  AssetReader * LoadAsset(std::string filename);

  Platform & platform() { return platform_; }

  void set_asset_reader_factory_module(sp<AssetReaderFactoryModule> asset_reader_factory_module) {
    asset_reader_factory_module_ = asset_reader_factory_module;
  }

  sp<PersistenceModule> persistence_module() { return persistence_module_; }
  void set_persistence_module(sp<PersistenceModule> persistence_module) {
    persistence_module_ = persistence_module;
  }

  sp<AdModule> ad_module() { return ad_module_; }
  void set_ad_module(sp<AdModule> ad_module) { ad_module_ = ad_module; }

  sp<AnalyticsModule> analytics_module() { return analytics_module_; }
  void set_analytics_module(sp<AnalyticsModule> analytics_module) {
    analytics_module_ = analytics_module;
  }

  sp<AppStoreModule> app_store_module() { return app_store_module_; }
  void set_app_store_module(sp<AppStoreModule> app_store_module) {
    app_store_module_ = app_store_module;
  }

  sp<InputModule> input_module() { return input_module_; }
  void set_input_module(sp<InputModule> input_module) { input_module_ = input_module; }

  sp<SharkSound::SoundController> sound() { return sound_controller_; }
  void set_sound(sp<SharkSound::SoundController> sound_controller) {
    sound_controller_ = sound_controller;
  }

  ResourceLoader &resource_loader() { return resource_loader_; }

  void load_positions(AssetReader &file) { positions_->LoadFile(file); }
  GamePoint position(std::string name) { return positions_->position(name); }

  // TODO consider refactoring this information exposure for game vs. platform, using inheritance.
  ScreenSize screen_size() { return screen_size_; }
  void set_screen_size(ScreenSize screen_size) { screen_size_ = screen_size; }

  ScreenPoint screen_offset() { return screen_offset_; }
  void set_screen_offset(ScreenPoint screen_offset) { screen_offset_ = screen_offset; }

  double screen_to_game_point_ratio_x() { return screen_to_game_point_ratio_x_; }
  double screen_to_game_point_ratio_y() { return screen_to_game_point_ratio_y_; }
  void set_screen_to_game_point_ratios(double ratio_x, double ratio_y) {
    screen_to_game_point_ratio_x_ = ratio_x;
    screen_to_game_point_ratio_y_ = ratio_y;
  }

  ScreenSize game_size_to_screen_size(GameSize game_size_) {
    return screen_size_make(game_size_.width * screen_to_game_point_ratio_x_,
                            game_size_.height * screen_to_game_point_ratio_y_);
  }
  ScreenPoint game_point_to_screen_point(GamePoint game_point_) {
    return screen_point_make(game_point_.x * screen_to_game_point_ratio_x_ + screen_offset_.x,
                             game_point_.y * screen_to_game_point_ratio_y_ + screen_offset_.y);
  }
  GameSize screen_size_to_game_size(ScreenSize screen_size_) {
    return game_size_make(screen_size_.width / screen_to_game_point_ratio_x_,
                          screen_size_.height / screen_to_game_point_ratio_y_);
  }
  GamePoint screen_point_to_game_point(ScreenPoint screen_point_) {
    return game_point_make((screen_point_.x - screen_offset_.x) / screen_to_game_point_ratio_x_,
                           (screen_point_.y - screen_offset_.y) / screen_to_game_point_ratio_y_);
  }

 private:
  void ProcessInput();

  // Platform specific
  Platform platform_;
  sp<AssetReaderFactoryModule> asset_reader_factory_module_;
  sp<PersistenceModule> persistence_module_;
  sp<AdModule> ad_module_;
  sp<AnalyticsModule> analytics_module_;
  sp<AppStoreModule> app_store_module_;
  sp<InputModule> input_module_;
  sp<SharkSound::SoundController> sound_controller_;

  ResourceLoader resource_loader_;
  sp<Positions> positions_;
  StagedVector<EngineView> views_;
  std::vector<Touch> touches_began_;
  std::vector<Touch> touches_moved_;
  std::vector<Touch> touches_ended_;
  std::vector<std::pair<Touch, unsigned int> > potential_tap_touches_;
  std::vector<int> keys_pressed_;
  float mouse_delta_x_;
  float mouse_delta_y_;
  ScreenSize screen_size_;
  ScreenPoint screen_offset_;
  double screen_to_game_point_ratio_x_;
  double screen_to_game_point_ratio_y_;
  unsigned int game_tick_;
};

#endif
