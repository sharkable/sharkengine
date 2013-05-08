//
//  composite_entity.cc
//  GameEngine
//
//  Created by Jon Sharkey on 2013-05-07.
//  Copyright 2013 Sharkable. All rights reserved.
//

#include "gameengine/entities/composite_entity.h"

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
