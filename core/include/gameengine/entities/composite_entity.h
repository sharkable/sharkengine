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

#include "gameengine/coordinates/coordinate_types.h"
#include "gameengine/entities/animatable.h"

class Touch;

class CompositeEntity : public Animatable {
 public:
  CompositeEntity() : Animatable() {};
  CompositeEntity(GamePoint position) : Animatable(position) {};
  ~CompositeEntity();

  void AddEntity(ViewEntity *entity);

  // ViewEntity
  void Update();
  void Render(GamePoint offset);
  bool TouchBegan(GamePoint offset, Touch touches);
  void TouchMoved(GamePoint offset, Touch touches);
  void TouchEnded(GamePoint offset, Touch touches);
  void ClearTouches();
  void SetEngineView(EngineView *engine_view);

 protected:
  std::vector<ViewEntity *> entities_;
};

#endif
