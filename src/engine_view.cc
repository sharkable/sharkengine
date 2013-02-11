//
//  engine_view.cc
//  AirHockey
//
//  Created by Jonathan Sharkey on 10-04-10.
//  Copyright 2010 Sharkable. All rights reserved.
//

#include "gameengine/engine_view.h"

#include "gameengine/game_engine.h"
#include "gameengine/view_entity.h"

EngineView::EngineView(sp<GameEngine> game_engine) : game_engine_(game_engine) {
}

void EngineView::Update() {
  for (int i = 0; i < entities_.size(); i++) {
    entities_[i]->Update();
  }
}

void EngineView::Render() {
  for (int i = 0; i < entities_.size(); i++) {
    entities_[i]->Render();
  }
}

void EngineView::TouchesBegan(vector<Touch> touches) {
  for (int i = 0; i < entities_.size(); i++) {
    entities_[i]->TouchesBegan(touches);
  }
}

void EngineView::TouchesMoved(vector<Touch> touches) {
  for (int i = 0; i < entities_.size(); i++) {
    entities_[i]->TouchesMoved(touches);
  }
}

void EngineView::TouchesEnded(vector<Touch> touches) {
  for (int i = 0; i < entities_.size(); i++) {
    entities_[i]->TouchesEnded(touches);
  }
}

void EngineView::ClearTouches() {
  for (int i = 0; i < entities_.size(); i++) {
    entities_[i]->ClearTouches();
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
  for (vector<sp<ViewEntity> >::iterator i = entities_.begin(); i != entities_.end(); i++) {
    if (*i == entity) {
      entities_.erase(i);
      break;
    }
  }
}
