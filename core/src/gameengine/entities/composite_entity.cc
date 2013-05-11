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
  Animatable::Update();
  for (auto i = entities_.begin(); i != entities_.end(); i++) {
    (*i)->Update();
  }
}

void CompositeEntity::Render(GamePoint offset) {
  GamePoint composite_offset = position() + offset;
  for (auto i = entities_.begin(); i != entities_.end(); i++) {
    (*i)->Render(composite_offset);
  }
}

bool CompositeEntity::TouchesBegan(GamePoint offset, vector<Touch> touches) {
  GamePoint composite_offset = position() + offset;
  for (auto i = entities_.rbegin(); i != entities_.rend(); i++) {
    if ((*i)->TouchesBegan(composite_offset, touches)) {
      return true;
    }
  }
  return false;
}

void CompositeEntity::TouchesMoved(GamePoint offset, vector<Touch> touches) {
  GamePoint composite_offset = position() + offset;
  for (auto i = entities_.rbegin(); i != entities_.rend(); i++) {
    (*i)->TouchesMoved(composite_offset, touches);
  }
}

void CompositeEntity::TouchesEnded(GamePoint offset, vector<Touch> touches) {
  GamePoint composite_offset = position() + offset;
  for (auto i = entities_.rbegin(); i != entities_.rend(); i++) {
    (*i)->TouchesEnded(composite_offset, touches);
  }
}

void CompositeEntity::ClearTouches() {
  for (auto i = entities_.rbegin(); i != entities_.rend(); i++) {
    (*i)->ClearTouches();
  }
}