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

using std::vector;

EngineView::EngineView(GameEngine *game_engine)
    : game_engine_(game_engine),
      is_visible_(false) {
}

void EngineView::Update() {
  entities_.Commit();
  for (auto i = entities_.Begin(); i != entities_.End(); i++) {
    (*i)->Update();
  }
}

void EngineView::Render() {
  for (auto i = entities_.Begin(); i != entities_.End(); i++) {
    (*i)->Render(kGamePointZero);
  }
}

bool EngineView::IsCapturingTouches() {
  return true;
}

void EngineView::TouchesBegan(vector<Touch> touches) {
  for (auto i = touches.begin(); i != touches.end(); i++) {
    // Iterate backwards. The items on top get priority to capture touches.
    for (auto j = entities_.ReverseBegin(); j != entities_.ReverseEnd(); j++) {
      if ((*j)->TouchBegan(kGamePointZero, *i)) {
        break;
      }
    }
  }
}

void EngineView::TouchesMoved(vector<Touch> touches) {
  for (auto i = touches.begin(); i != touches.end(); i++) {
    for (auto j = entities_.Begin(); j != entities_.End(); j++) {
      (*j)->TouchMoved(kGamePointZero, *i);
    }
  }
}

void EngineView::TouchesEnded(vector<Touch> touches) {
  for (auto i = touches.begin(); i != touches.end(); i++) {
    for (auto j = entities_.Begin(); j != entities_.End(); j++) {
      (*j)->TouchEnded(kGamePointZero, *i);
    }
  }
}

void EngineView::TouchTapped(Touch touch) {
  for (auto i = entities_.Begin(); i != entities_.End(); i++) {
    (*i)->TouchTapped(kGamePointZero, touch);
  }
}

void EngineView::HandleMouseDelta(float delta_x, float delta_y) {
  for (auto i = entities_.Begin(); i != entities_.End(); i++) {
    (*i)->HandleMouseDelta(delta_x, delta_y);
  }
}

void EngineView::ClearTouches() {
  for (auto i = entities_.Begin(); i != entities_.End(); i++) {
    (*i)->ClearTouches();
  }
}

bool EngineView::HandleBackButton() {
  return false;
}

void EngineView::AddEntity(ViewEntity *entity, bool managed_memory) {
  entity->SetEngineView(this);
  entities_.PushBack(entity, managed_memory);
}

void EngineView::InsertEntityBefore(ViewEntity *entity, ViewEntity *existing_entity,
                                    bool managed_memory) {
  entity->SetEngineView(this);
  entities_.InsertBefore(entity, existing_entity, managed_memory);
}

void EngineView::InsertEntityAfter(ViewEntity *entity, ViewEntity *existing_entity,
                                   bool managed_memory) {
  entity->SetEngineView(this);
  entities_.InsertAfter(entity, existing_entity, managed_memory);
}

void EngineView::RemoveEntity(ViewEntity *entity) {
  entity->SetEngineView(NULL);
  entities_.Erase(entity);
}
