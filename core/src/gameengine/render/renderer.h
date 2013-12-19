//
//  renderer.h
//  GameEngine
//
//  Created by Jon Sharkey on 2013-12-03.
//  Copyright 2013 Sharkable. All rights reserved.
//

#ifndef GAMEENGINE_RENDER_RENDERER_H_
#define GAMEENGINE_RENDER_RENDERER_H_

#include "gameengine/coordinates/coordinate_system.h"

class Renderer {
 public:
  virtual ~Renderer() {}
  virtual void Render(CoordinateSystem const &coordinate_system) = 0;
  virtual float SortValue() { return 0.f; }
};

#endif
