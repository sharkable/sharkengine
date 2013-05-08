//
//  composite_entity.h
//  GameEngine
//
//  Created by Jon Sharkey on 2013-05-07.
//  Copyright 2013 Sharkable. All rights reserved.
//

#ifndef GAMEENGINE_ENTITIES_COMPOSITEENTITY_H_
#define GAMEENGINE_ENTITIES_COMPOSITEENTITY_H_

#include <vector>

#include "gameengine/coordinate_types.h"
#include "gameengine/view_entity.h"

class CompositeEntity : public ViewEntity {
 public:
  void AddEntity(sp<ViewEntity> entity);

  // ViewEntity
  void Update();
  void Render();

 private:
  std::vector<sp<ViewEntity> > entities_;
};

#endif
