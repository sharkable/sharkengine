//
//  game_engine.cc
//  GameEngine
//
//  Created by Jon Sharkey on 2010-04-10.
//  Copyright 2010 Sharkable. All rights reserved.
//

#include "gameengine/game_engine.h"

#include "gameengine/engine_view.h"

GameEngine::GameEngine()
    : platform_type_(kPlatformTypePhone),
      screen_offset_(kScreenPointZero),
      game_size_(kGameSizeZero),
      game_to_screen_point_ratio_x_(0),
      game_to_screen_point_ratio_y_(0),
      screen_to_game_point_ratio_x_(0),
      screen_to_game_point_ratio_y_(0) {
  positions_ = sp<Positions>(new Positions());
}

void GameEngine::SetScreenSize(ScreenSize screen_size, GameSize game_size) {
  game_size_ = game_size;
  game_to_screen_point_ratio_x_ = screen_size.width / game_size.width;
  game_to_screen_point_ratio_y_ = screen_size.height / game_size.height;
  screen_to_game_point_ratio_x_ = game_size.width / screen_size.width;
  screen_to_game_point_ratio_y_ = game_size.height / screen_size.height;
}

void GameEngine::SetScreenOffset(ScreenPoint screen_offset) {
  screen_offset_ = screen_offset;
}

void GameEngine::Update() {
  if (next_views_.size() > 0) {
    if (views_.size()) {
      views_.back()->ClearTouches();
    }
    views_ = next_views_;
    views_.back()->ViewIsShown();
    next_views_.clear();
  }

  assert(views_.size() > 0);

  // Process input.
  sp<EngineView> top_view = views_.back();

  if (touches_began_.size() > 0) {
    top_view->TouchesBegan(touches_began_);
    touches_began_.clear();
  }
  if (touches_moved_.size() > 0) {
    top_view->TouchesMoved(touches_moved_);
    touches_moved_.clear();
  }
  if (touches_ended_.size() > 0) {
    top_view->TouchesEnded(touches_ended_);
    touches_ended_.clear();
  }

  // Update views.
  for (int i = 0; i < views_.size(); i++) {
    s_log("about to update %s", typeid(*views_[i]).name());
    views_[i]->Update();
    s_log("updated %s", typeid(*views_[i]).name());
  }
}

void GameEngine::Render() {
  for (int i = 0; i < views_.size(); i++) {
    s_log("about to render %s", typeid(*views_[i]).name());
    views_[i]->Render();
    s_log("rendered %s", typeid(*views_[i]).name());
  }
}

void GameEngine::ClearTouches() {
  for (int i = 0; i < views_.size(); i++) {
    views_[i]->ClearTouches();
  }
}

void GameEngine::PushView(sp<EngineView> view) {
  s_log("pushing: %s", typeid(*view).name());
  if (next_views_.size() == 0) {
    next_views_ = views_;
  }
  next_views_.push_back(view);
}

void GameEngine::PopView() {
  assert(views_.size() > 0);
  if (next_views_.size() == 0) {
    next_views_ = views_;
  }
  next_views_.pop_back();
}

void GameEngine::RemoveView(EngineView *view) {
  if (next_views_.size() == 0) {
    next_views_ = views_;
  }
  for (auto i = next_views_.begin(); i != next_views_.end(); i++) {
    if (i->get() == view) {
      i = next_views_.erase(i);
    }
  }
}

void GameEngine::SetRootView(sp<EngineView> view) {
  next_views_.clear();
  next_views_.push_back(view);
}
