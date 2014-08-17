//
//  shark_engine.cc
//  SharkEngine
//
//  Created by Jon Sharkey on 2010-04-10.
//  Copyright 2010 Sharkable. All rights reserved.
//

#include "sharkengine/shark_engine.h"

#include <cmath>

#include "sharkengine/modules/ad_module.h"
#include "sharkengine/modules/analytics_module.h"
#include "sharkengine/modules/app_store_module.h"
#include "sharkengine/modules/asset_reader_factory_module.h"
#include "sharkengine/modules/input_module.h"
#include "sharkengine/modules/persistence_module.h"
#include "sharkengine/input/input_handler.h"
#include "sharkengine/render/renderer.h"
#include "sharkengine/simulation/simulator.h"

SharkEngine::SharkEngine()
    : simulator_(nullptr),
      renderer_(nullptr),
      input_handler_(nullptr),
      resource_loader_(*this),
      mouse_delta_x_(0),
      mouse_delta_y_(0),
      screen_size_(kScreenSizeZero),
      screen_offset_(kScreenPointZero),
      screen_to_game_point_ratio_x_(1),
      screen_to_game_point_ratio_y_(1),
      game_tick_(0) {
  persistence_module_.reset(new PersistenceModule());
  ad_module_.reset(new AdModule());
  analytics_module_.reset(new AnalyticsModule());
  app_store_module_.reset(new AppStoreModule());
  input_module_.reset(new InputModule());

  positions_ = sp<Positions>(new Positions());
}


#pragma mark - Platform functions

void SharkEngine::Update() {
  shark_assert(input_handler_, "No InputHandler found.");
  shark_assert(simulator_, "No Simulator found.");
  input_manager_.HandleEvents(*input_handler_);
  simulator_->SimulateStep();
  input_module_->SimulateStep();
  game_tick_++;
}

void SharkEngine::Render() {
  shark_assert(renderer_, "No Renderer found.");
  renderer_->Render(CoordinateSystem::BaseSystem());
}


#pragma mark - App functions

void SharkEngine::SetSimulator(Simulator *simulator) {
  simulator_ = simulator;
}

void SharkEngine::SetRenderer(Renderer *renderer) {
  renderer_ = renderer;
}

void SharkEngine::SetInputHandler(InputHandler *input_handler) {
  input_handler_ = input_handler;
}

sp<AssetReader> SharkEngine::LoadAsset(std::string filename) {
  return sp<AssetReader>(asset_reader_factory_module_->CreateAssetReader(filename));
}
