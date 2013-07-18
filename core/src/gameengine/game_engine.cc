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
      resource_loader_(*this),
      screen_size_(kScreenSizeZero),
      screen_offset_(kScreenPointZero),
      screen_to_game_point_ratio_(1) {
  positions_ = sp<Positions>(new Positions());
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
  sp<EngineView> touch_view;
  for (auto i = views_.rbegin(); i != views_.rend(); i++) {
    if ((*i)->IsCapturingTouches()) {
      touch_view = *i;
      break;
    }
  }
  if (touch_view) {
    if (touches_began_.size() > 0) {
      touch_view->TouchesBegan(touches_began_);
      touches_began_.clear();
    }
    if (touches_moved_.size() > 0) {
      touch_view->TouchesMoved(touches_moved_);
      touches_moved_.clear();
    }
    if (touches_ended_.size() > 0) {
      touch_view->TouchesEnded(touches_ended_);
      touches_ended_.clear();
    }
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

void GameEngine::NotifyPause() {
  for (int i = 0; i < views_.size(); i++) {
    views_[i]->NotifyPause();
  }
}

void GameEngine::ClearTouches() {
  for (int i = 0; i < views_.size(); i++) {
    views_[i]->ClearTouches();
  }
}

void GameEngine::AddTouchBegan(Touch touch) {
  touches_began_.push_back(touch);
}

void GameEngine::AddTouchMoved(Touch touch) {
  touches_moved_.push_back(touch);
}

void GameEngine::AddTouchEnded(Touch touch) {
  touches_ended_.push_back(touch);
}

bool GameEngine::HandleBackButton() {
  if (views_.size() == 0) {
    return false;
  }
  return views_.back()->HandleBackButton();
}

void GameEngine::PushView(sp<EngineView> view) {
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
      break;
    }
  }
}

void GameEngine::SetRootView(sp<EngineView> view) {
  next_views_.clear();
  next_views_.push_back(view);
}
