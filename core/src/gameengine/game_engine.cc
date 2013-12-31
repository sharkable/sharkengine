//
//  game_engine.cc
//  GameEngine
//
//  Created by Jon Sharkey on 2010-04-10.
//  Copyright 2010 Sharkable. All rights reserved.
//

#include "gameengine/game_engine.h"

#include <cmath>

#include "gameengine/modules/ad_module.h"
#include "gameengine/modules/analytics_module.h"
#include "gameengine/modules/app_store_module.h"
#include "gameengine/modules/asset_reader_factory_module.h"
#include "gameengine/modules/input_module.h"
#include "gameengine/modules/persistence_module.h"
#include "gameengine/input/input_handler.h"
#include "gameengine/render/renderer.h"
#include "gameengine/simulation/simulator.h"

GameEngine::GameEngine()
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

  pthread_mutex_init(&user_input_mutex_, NULL);
}

GameEngine::~GameEngine() {
  pthread_mutex_destroy(&user_input_mutex_);
}


#pragma mark - Platform functions

void GameEngine::Update() {
  shark_assert(simulator_, "No Renderer found.");
  ProcessInput();
  simulator_->SimulateStep();
  game_tick_++;
}

void GameEngine::Render() {
  shark_assert(renderer_, "No Renderer found.");
  renderer_->Render(CoordinateSystem::BaseSystem());
}

void GameEngine::AddInputEvent(const InputEvent &event) {
  shark_assert(!pthread_mutex_lock(&user_input_mutex_), "Error locking mutex.");
  input_events_.push_back(event);
  shark_assert(!pthread_mutex_unlock(&user_input_mutex_), "Error unlocking mutex.");
}


#pragma mark - App functions

void GameEngine::SetSimulator(Simulator *simulator) {
  simulator_ = simulator;
}

void GameEngine::SetRenderer(Renderer *renderer) {
  renderer_ = renderer;
}

void GameEngine::SetInputHandler(InputHandler *input_handler) {
  input_handler_ = input_handler;
}

sp<AssetReader> GameEngine::LoadAsset(std::string filename) {
  return sp<AssetReader>(asset_reader_factory_module_->CreateAssetReader(filename));
}


#pragma mark - private

void GameEngine::ProcessInput() {
  shark_assert(!pthread_mutex_lock(&user_input_mutex_), "Error locking mutex.");

  shark_assert(input_handler_, "No InputHandler found.");
  for (InputEvent event : input_events_) {
    input_handler_->HandleInputEvent(event);
  }
  input_events_.clear();

  shark_assert(!pthread_mutex_unlock(&user_input_mutex_), "Error unlocking mutex.");
}
