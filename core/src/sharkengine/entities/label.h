//
//  label.h
//  SharkEngine
//
//  Created by Jon Sharkey on 2013-09-18.
//  Copyright 2013 Sharkable. All rights reserved.
//

#ifndef SHARKENGINE_ENTITIES_LABEL_H_
#define SHARKENGINE_ENTITIES_LABEL_H_

#include <string>

#include "sharkengine/coordinates/coordinate_types.h"
#include "sharkengine/entities/animatable.h"
#include "sharkengine/render/renderer.h"

class SharkEngine;

class Label : public Animatable, public Renderer {
 public:
  Label(SharkEngine &game_engine, GamePoint position);

  const std::string & Text();
  void SetText(const std::string &text);
  GameRect Rect();

  // Renderer
  void Render(CoordinateSystem const &coordinate_system);

 private:
  GameSize CalculateSize();

  std::string text_;
  GameSize size_;
};

#endif
