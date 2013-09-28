//
//  game_engine.cc
//  GameEngine
//
//  Created by Jon Sharkey on 2010-04-10.
//  Copyright 2010 Sharkable. All rights reserved.
//

#include "gameengine/game_engine.h"

#include "gameengine/engine_view.h"
#include "gameengine/modules/ad_module.h"
#include "gameengine/modules/analytics_module.h"
#include "gameengine/modules/app_store_module.h"
#include "gameengine/modules/asset_reader_factory_module.h"
#include "gameengine/modules/input_module.h"
#include "gameengine/modules/label_factory_module.h"
#include "gameengine/modules/persistence_module.h"

GameEngine::GameEngine()
    : platform_type_(kPlatformTypePhone),
      resource_loader_(*this),
      mouse_delta_x_(0),
      mouse_delta_y_(0),
      screen_size_(kScreenSizeZero),
      screen_offset_(kScreenPointZero),
      screen_to_game_point_ratio_x_(1),
      screen_to_game_point_ratio_y_(1) {
  persistence_module_.reset(new PersistenceModule());
  ad_module_.reset(new AdModule());
  analytics_module_.reset(new AnalyticsModule());
  app_store_module_.reset(new AppStoreModule());
  input_module_.reset(new InputModule());

  positions_ = sp<Positions>(new Positions());
}

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
  touches_began_.push_back(touch);
}

void GameEngine::AddTouchMoved(Touch touch) {
  touches_moved_.push_back(touch);
}

void GameEngine::AddTouchEnded(Touch touch) {
  touches_ended_.push_back(touch);
}

void GameEngine::AddMouseDelta(float delta_x, float delta_y) {
  mouse_delta_x_ += delta_x;
  mouse_delta_y_ += delta_y;
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

void GameEngine::PushView(EngineView *view) {
  view->set_is_visible(true);
  views_.PushBack(view, true);
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
  return asset_reader_factory_module_->CreateAssetReader(filename);
}

sp<Label> GameEngine::CreateLabel(const std::string &text, GamePoint position) {
  return label_factory_module_->CreateLabel(text, position);
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

  if (touch_view) {
    if (touches_began_.size() > 0) {
      potential_tap_touches_.insert(potential_tap_touches_.end(), touches_began_.begin(),
                                    touches_began_.end());
    }
    for (auto i = touches_moved_.begin(); i != touches_moved_.end(); i++) {
      for (auto j = potential_tap_touches_.begin(); j != potential_tap_touches_.end(); j++) {
        if (i->identifier() == j->identifier()) {
          potential_tap_touches_.erase(j);
          break;
        }
      }
    }
    for (auto i = touches_ended_.begin(); i != touches_ended_.end(); i++) {
      for (auto j = potential_tap_touches_.begin(); j != potential_tap_touches_.end();) {
        if (i->identifier() == j->identifier()) {
          touch_view->TouchTapped(*i);
          j = potential_tap_touches_.erase(j);
        } else {
          j++;
        }
      }
    }

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
    // TODO should this be called if both values are 0?
    touch_view->HandleMouseDelta(mouse_delta_x_, mouse_delta_y_);
    mouse_delta_x_ = 0;
    mouse_delta_y_ = 0;
  }
}
