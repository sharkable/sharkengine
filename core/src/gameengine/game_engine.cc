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

GameEngine::GameEngine()
    : resource_loader_(*this),
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
  if (views_.HasStagedChanges()) {
    if (views_.Size() > 0) {
      views_.Back()->ViewDidLoseFocus();
      views_.Back()->ClearTouches();
    }
    views_.StagedBack()->ViewDidGainFocus();
    views_.Commit();
  }

  assert(views_.Size() > 0);

  ProcessInput();

  // Update views.
  for (auto i = views_.Begin(); i != views_.End(); i++) {
    (*i)->Update();
  }
  game_tick_++;
}

void GameEngine::Render() {
  for (auto i = views_.Begin(); i != views_.End(); i++) {
    (*i)->Render();
  }
}

void GameEngine::NotifyPause() {
  for (auto i = views_.Begin(); i != views_.End(); i++) {
    (*i)->NotifyPause();
  }
}

void GameEngine::ClearTouches() {
  for (auto i = views_.Begin(); i != views_.End(); i++) {
    (*i)->ClearTouches();
  }
}

void GameEngine::AddTouchBegan(Touch touch) {
  shark_assert(!pthread_mutex_lock(&user_input_mutex_), "Error locking mutex.");
  touches_began_.push_back(touch);
  shark_assert(!pthread_mutex_unlock(&user_input_mutex_), "Error unlocking mutex.");
}

void GameEngine::AddTouchMoved(Touch touch) {
  shark_assert(!pthread_mutex_lock(&user_input_mutex_), "Error locking mutex.");
  touches_moved_.push_back(touch);
  shark_assert(!pthread_mutex_unlock(&user_input_mutex_), "Error unlocking mutex.");
}

void GameEngine::AddTouchEnded(Touch touch) {
  shark_assert(!pthread_mutex_lock(&user_input_mutex_), "Error locking mutex.");
  touches_ended_.push_back(touch);
  shark_assert(!pthread_mutex_unlock(&user_input_mutex_), "Error unlocking mutex.");
}

void GameEngine::AddKeyPressed(int key) {
  shark_assert(!pthread_mutex_lock(&user_input_mutex_), "Error locking mutex.");
  keys_pressed_.push_back(key);
  shark_assert(!pthread_mutex_unlock(&user_input_mutex_), "Error unlocking mutex.");
}

void GameEngine::AddMouseDelta(float delta_x, float delta_y) {
  shark_assert(!pthread_mutex_lock(&user_input_mutex_), "Error locking mutex.");
  mouse_delta_x_ += delta_x;
  mouse_delta_y_ += delta_y;
  shark_assert(!pthread_mutex_unlock(&user_input_mutex_), "Error unlocking mutex.");
}

bool GameEngine::HandleBackButton() {
  if (views_.Size() == 0) {
    return false;
  }
  return views_.Back()->HandleBackButton();
}

void GameEngine::HandlePauseButton() {
  if (views_.Size() != 0) {
    views_.Back()->HandlePauseButton();
  }
}


#pragma mark - App functions

void GameEngine::PushView(EngineView *view) {
  view->set_is_visible(true);
  views_.PushBack(view, true);
}

void GameEngine::InsertViewAfter(EngineView *view, EngineView *existing_view) {
  view->set_is_visible(true);
  views_.InsertAfter(view, existing_view);
}

void GameEngine::PopView() {
  assert(views_.StagedSize() > 0);
  views_.StagedBack()->set_is_visible(false);
  views_.PopBack();
}

void GameEngine::RemoveView(EngineView *view) {
  view->set_is_visible(false);
  views_.Erase(view);
}

void GameEngine::SetRootView(EngineView *view) {
  view->set_is_visible(true);
  views_.Clear();
  views_.PushBack(view, true);
}

sp<AssetReader> GameEngine::LoadAsset(std::string filename) {
  return sp<AssetReader>(asset_reader_factory_module_->CreateAssetReader(filename));
}


#pragma mark - private

void GameEngine::ProcessInput() {
  EngineView *touch_view = NULL;
  for (auto i = views_.ReverseBegin(); i != views_.ReverseEnd(); i++) {
    if ((*i)->IsCapturingTouches()) {
      touch_view = *i;
      break;
    }
  }
  shark_assert(touch_view, "No touch view found.");

  shark_assert(!pthread_mutex_lock(&user_input_mutex_), "Error locking mutex.");

  if (touches_began_.size() > 0) {
    // This removes captures touches, so they can't use considered for taps.
    touch_view->TouchesBegan(touches_began_);
  }
  if (touches_moved_.size() > 0) {
    touch_view->TouchesMoved(touches_moved_);
  }
  if (touches_ended_.size() > 0) {
    touch_view->TouchesEnded(touches_ended_);
  }
  if (keys_pressed_.size() > 0) {
    touch_view->KeysPressed(keys_pressed_);
  }
  // TODO should this be called if both values are 0?
  touch_view->HandleMouseDelta(mouse_delta_x_, mouse_delta_y_);
  mouse_delta_x_ = 0;
  mouse_delta_y_ = 0;

  if (touch_view) {
    // Erase presses that have existed too long to be a tap.
    for (auto i = potential_tap_touches_.begin(); i != potential_tap_touches_.end();) {
      if (game_tick_ - i->second > 10) {
        i = potential_tap_touches_.erase(i);
      } else {
        i++;
      }
    }
    // Add new touches as potential taps.
    if (touches_began_.size() > 0) {
      for (auto i = touches_began_.begin(); i != touches_began_.end(); i++) {
        potential_tap_touches_.push_back(std::make_pair(*i, game_tick_));
      }
    }
    for (auto i = touches_moved_.begin(); i != touches_moved_.end(); i++) {
      for (auto j = potential_tap_touches_.begin(); j != potential_tap_touches_.end(); j++) {
        if (i->identifier() == j->first.identifier()) {
          float dx = i->location().x - j->first.location().x;
          float dy = i->location().y - j->first.location().y;
          if (fabs(dx) >= 20.f || fabs(dy) >= 20.f) {
            potential_tap_touches_.erase(j);
          }
          break;
        }
      }
    }
    for (auto i = touches_ended_.begin(); i != touches_ended_.end(); i++) {
      for (auto j = potential_tap_touches_.begin(); j != potential_tap_touches_.end();) {
        if (i->identifier() == j->first.identifier()) {
          touch_view->TouchTapped(*i);
          j = potential_tap_touches_.erase(j);
        } else {
          j++;
        }
      }
    }
  }

  touches_began_.clear();
  touches_moved_.clear();
  touches_ended_.clear();
  keys_pressed_.clear();

  shark_assert(!pthread_mutex_unlock(&user_input_mutex_), "Error unlocking mutex.");
}
