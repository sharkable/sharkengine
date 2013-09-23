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

EngineView::EngineView(GameEngine *game_engine)
    : game_engine_(game_engine),
      is_visible_(false) {
}

void EngineView::Update() {
  for (auto i = entities_.begin(); i != entities_.end(); i++) {
    (*i)->Update();
  }
}

void EngineView::Render() {
  for (auto i = entities_.begin(); i != entities_.end(); i++) {
    (*i)->Render(kGamePointZero);
  }
}

bool EngineView::IsCapturingTouches() {
  return true;
}

void EngineView::TouchesBegan(vector<Touch> touches) {
  // Iterate backwards. The items on top get priority to capture touches.
  for (auto i = entities_.rbegin(); i != entities_.rend(); i++) {
    if ((*i)->TouchesBegan(kGamePointZero, touches)) {
      break;
    }
  }
}

void EngineView::TouchesMoved(vector<Touch> touches) {
  for (auto i = entities_.begin(); i != entities_.end(); i++) {
    (*i)->TouchesMoved(kGamePointZero, touches);
  }
}

void EngineView::TouchesEnded(vector<Touch> touches) {
  for (auto i = entities_.begin(); i != entities_.end(); i++) {
    (*i)->TouchesEnded(kGamePointZero, touches);
  }
}

void EngineView::HandleMouseDelta(float delta_x, float delta_y) {
  for (auto i = entities_.begin(); i != entities_.end(); i++) {
    (*i)->HandleMouseDelta(delta_x, delta_y);
  }
}

void EngineView::ClearTouches() {
  for (auto i = entities_.begin(); i != entities_.end(); i++) {
    (*i)->ClearTouches();
  }
}

bool EngineView::HandleBackButton() {
  return false;
}

void EngineView::AddEntity(ViewEntity *entity) {
  entity->set_engine_view(this);
  entities_.push_back(sp<ViewEntity>(entity));
}

void EngineView::AddEntity(sp<ViewEntity> entity) {
  assert(entity);
  entity->set_engine_view(this);
  entities_.push_back(entity);
}

void EngineView::InsertEntityBefore(ViewEntity *entity, ViewEntity *existing_entity) {
  InsertEntityBefore(sp<ViewEntity>(entity), existing_entity);
}

void EngineView::InsertEntityBefore(sp<ViewEntity> entity, ViewEntity *existing_entity) {
  for (auto i = entities_.begin(); i != entities_.end(); i++) {
    if (i->get() == existing_entity) {
      entity->set_engine_view(this);
      entities_.insert(i, entity);
      return;
    }
  }
  // Failed to find |existing_entity|.
  assert(false);
}

void EngineView::InsertEntityAfter(ViewEntity *entity, ViewEntity *existing_entity) {
  InsertEntityAfter(sp<ViewEntity>(entity), existing_entity);
}

void EngineView::InsertEntityAfter(sp<ViewEntity> entity, ViewEntity *existing_entity) {
  for (auto i = entities_.begin(); i != entities_.end(); i++) {
    if (i->get() == existing_entity) {
      entity->set_engine_view(this);
      entities_.insert(i + 1, entity);
      return;
    }
  }
  // Failed to find |existing_entity|.
  assert(false);
}

void EngineView::RemoveEntity(sp<ViewEntity> entity) {
  for (auto i = entities_.begin(); i != entities_.end(); i++) {
    if (*i == entity) {
      entity->set_engine_view(NULL);
      entities_.erase(i);
      break;
    }
  }
}

