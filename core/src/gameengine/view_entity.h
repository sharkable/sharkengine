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

#include "gameengine/touch.h"
#include "gameengine/coordinates/coordinate_types.h"

class EngineView;

class ViewEntity {
 public:
  ViewEntity() : engine_view_(NULL) {}
  virtual ~ViewEntity() {}

  virtual void Update() {};

  virtual void Render(GamePoint render_offset, float render_angle) {}
  virtual void Render(GamePoint render_offset) { Render(render_offset, 0.f); }
  virtual bool TouchBegan(GamePoint offset, Touch touch) { return false; }
  virtual void TouchMoved(GamePoint offset, Touch touch) {}
  virtual void TouchEnded(GamePoint offset, Touch touch) {}
  virtual void TouchTapped(GamePoint offset, Touch touch) {}
  virtual void ClearTouches() {}
  virtual void KeyPressed(int key) {}
  virtual void HandleMouseDelta(float delta_x, float delta_y) {}
  virtual GameRect Rect() {
    shark_assert(false, "rect() is not supported for this ViewEntity of type %s.",
                 typeid(*this).name());
    return kGameRectZero;
  }

  // Accessors
  virtual EngineView * view() { return engine_view_; }

 private:
  virtual void SetEngineView(EngineView *engine_view) { engine_view_ = engine_view; }
  friend class EngineView;

  EngineView *engine_view_;  // weak
};

#endif
