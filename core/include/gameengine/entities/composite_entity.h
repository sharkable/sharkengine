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

#include "gameengine/entities/animatable.h"
#include "gameengine/coordinate_types.h"

class Touch;

class CompositeEntity : public Animatable {
 public:
  void AddEntity(sp<ViewEntity> entity);

  // ViewEntity
  void Update();
  void Render(GamePoint offset);
  bool TouchesBegan(GamePoint offset, std::vector<Touch> touches);
  void TouchesMoved(GamePoint offset, std::vector<Touch> touches);
  void TouchesEnded(GamePoint offset, std::vector<Touch> touches);
  void ClearTouches();

 private:
  std::vector<sp<ViewEntity> > entities_;
};

#endif
