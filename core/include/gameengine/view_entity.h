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

class Touch;

class ViewEntity {
 public:
  virtual void Update() = 0;
  virtual void Render(GamePoint offset) = 0;
  virtual bool TouchesBegan(std::vector<Touch> touches) { return false; }
  virtual void TouchesMoved(std::vector<Touch> touches) {}
  virtual void TouchesEnded(std::vector<Touch> touches) {}
  virtual void ClearTouches() {}
};

#endif
