//
//  engine_view.cc
//  GameEngine
//
//  Created by Jon Sharkey on 2010-04-10.
//  Copyright 2010 Sharkable. All rights reserved.
//

#include "gameengine/engine_view.h"

#include <algorithm>

#include "gameengine/game_engine.h"
#include "gameengine/touch.h"
#include "gameengine/view_entity.h"

using std::vector;

EngineView::EngineView(sp<GameEngine> game_engine) : game_engine_(game_engine) {
}

void EngineView::Update() {
  for (auto i = entities_.begin(); i != entities_.end(); i++) {
    (*i)->Update();
  }
}

void EngineView::Render() {
  for (auto i = entities_.begin(); i != entities_.end(); i++) {
    (*i)->Render();
  }
}

bool EngineView::IsCapturingTouches() {
  return true;
}

void EngineView::TouchesBegan(vector<Touch> touches) {
  // Iterate backwards. The items on top get priority to capture touches.
  for (auto i = entities_.rbegin(); i != entities_.rend(); i++) {
    if ((*i)->TouchesBegan(touches)) {
      break;
    }
  }
}

void EngineView::TouchesMoved(vector<Touch> touches) {
  for (auto i = entities_.begin(); i != entities_.end(); i++) {
    (*i)->TouchesMoved(touches);
  }
}

void EngineView::TouchesEnded(vector<Touch> touches) {
  for (auto i = entities_.begin(); i != entities_.end(); i++) {
    (*i)->TouchesEnded(touches);
  }
}

void EngineView::ClearTouches() {
  for (auto i = entities_.begin(); i != entities_.end(); i++) {
    (*i)->ClearTouches();
  }
}

void EngineView::AddEntity(ViewEntity *entity) {
  entities_.push_back(sp<ViewEntity>(entity));
}

void EngineView::AddEntity(sp<ViewEntity> entity) {
  assert(entity);
  entities_.push_back(entity);
}

void EngineView::RemoveEntity(sp<ViewEntity> entity) {
  for (auto i = entities_.begin(); i != entities_.end(); i++) {
    if (*i == entity) {
      entities_.erase(i);
      break;
    }
  }
}

bool EngineView::ContainsEntity(sp<ViewEntity> entity) {
  return std::find(entities_.begin(), entities_.end(), entity) != entities_.end();
}
