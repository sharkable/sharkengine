//
//  composite_entity.cc
//  GameEngine
//
//  Created by Jon Sharkey on 2013-05-07.
//  Copyright 2013 Sharkable. All rights reserved.
//

#include "gameengine/entities/composite_entity.h"
#include "gameengine/touch.h"

using std::vector;

void CompositeEntity::AddEntity(sp<ViewEntity> entity) {
  entities_.push_back(entity);
}


// ViewEntity

void CompositeEntity::Update() {
  for (auto i = entities_.begin(); i != entities_.end(); i++) {
    (*i)->Update();
  }
}

void CompositeEntity::Render() {
  for (auto i = entities_.begin(); i != entities_.end(); i++) {
    (*i)->Render();
  }
}

bool CompositeEntity::TouchesBegan(vector<Touch> touches) {
  for (auto i = entities_.rbegin(); i != entities_.rend(); i++) {
    if ((*i)->TouchesBegan(touches)) {
      return true;
    }
  }
  return false;
}

void CompositeEntity::TouchesMoved(vector<Touch> touches) {
  for (auto i = entities_.rbegin(); i != entities_.rend(); i++) {
    (*i)->TouchesMoved(touches);
  }
}

void CompositeEntity::TouchesEnded(vector<Touch> touches) {
  for (auto i = entities_.rbegin(); i != entities_.rend(); i++) {
    (*i)->TouchesEnded(touches);
  }
}

void CompositeEntity::ClearTouches() {
  for (auto i = entities_.rbegin(); i != entities_.rend(); i++) {
    (*i)->ClearTouches();
  }
}
