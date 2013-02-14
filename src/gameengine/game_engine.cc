//
//  game_engine.cc
//  AirHockey
//
//  Created by Jonathan Sharkey on 10-04-10.
//  Copyright 2010 Sharkable. All rights reserved.
//

#import "gameengine/game_engine.h"

#include "gameengine/engine_view.h"

GameEngine::GameEngine()
    : pop_on_next_(false),
      replace_on_next_(false),
      screen_offset_(kScreenPointZero),
      game_to_screen_point_ratio_x_(0),
      game_to_screen_point_ratio_y_(0),
      screen_to_game_point_ratio_x_(0),
      screen_to_game_point_ratio_y_(0) {
}

void GameEngine::SetScreenSize(ScreenSize screen_size, GameSize game_size) {
  game_to_screen_point_ratio_x_ = screen_size.width / game_size.width;
  game_to_screen_point_ratio_y_ = screen_size.height / game_size.height;
  screen_to_game_point_ratio_x_ = game_size.width / screen_size.width;
  screen_to_game_point_ratio_y_ = game_size.height / screen_size.height;
}

void GameEngine::SetScreenOffset(ScreenPoint screen_offset) {
  screen_offset_ = screen_offset;
}

void GameEngine::Update() {
  assert(views_.size() > 0);

  if (pop_on_next_) {
    views_.pop_back();
    views_.back()->ViewIsShown();
    pop_on_next_ = false;
  } else if (replace_on_next_) {
    views_.pop_back();
    views_.push_back(next_view_);
    next_view_->ViewIsShown();
    replace_on_next_ = false;
    next_view_.reset();
  }

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
    views_[i]->Update();
  }  
}

void GameEngine::Render() {
  for (int i = 0; i < views_.size(); i++) {
    views_[i]->Render();
  }
}

void GameEngine::ClearTouches() {
  for (int i = 0; i < views_.size(); i++) {
    views_[i]->ClearTouches();
  }
}

void GameEngine::PushView(sp<EngineView> view) {
  views_.push_back(view);
  view->ViewIsShown();
}

void GameEngine::PopView() {
  pop_on_next_ = true;
}

void GameEngine::SetRootView(sp<EngineView> view) {
  replace_on_next_ = true;
  next_view_ = view;
}
