//
//  view_entity.h
//  GameEngine
//
//  Created by Jon Sharkey on 2010-04-10.
//  Copyright 2010 Sharkable. All rights reserved.
//

#ifndef GAMEENGINE_VIEWENTITY_H_
#define GAMEENGINE_VIEWENTITY_H_

#include <vector>

#include "gameengine/coordinate_types.h"

class EngineView;
class Touch;

class ViewEntity {
 public:
  ViewEntity() : engine_view_(NULL) {}

  virtual void Update() = 0;
  virtual void Render(GamePoint offset) = 0;
  virtual bool TouchesBegan(GamePoint offset, std::vector<Touch> touches) { return false; }
  virtual void TouchesMoved(GamePoint offset, std::vector<Touch> touches) {}
  virtual void TouchesEnded(GamePoint offset, std::vector<Touch> touches) {}
  virtual void ClearTouches() {}
  virtual void HandleMouseDelta(float delta_x, float delta_y) {}

  // Accessors
  virtual EngineView * view() { return engine_view_; }

 private:
  virtual void set_engine_view(EngineView *engine_view) { engine_view_ = engine_view; }
  friend class EngineView;

  EngineView *engine_view_;  // weak
};

#endif
