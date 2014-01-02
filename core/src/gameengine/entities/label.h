//
//  label.h
//  GameEngine
//
//  Created by Jon Sharkey on 2013-09-18.
//  Copyright 2013 Sharkable. All rights reserved.
//

#ifndef GAMEENGINE_ENTITIES_LABEL_H_
#define GAMEENGINE_ENTITIES_LABEL_H_

#include <string>

#include "gameengine/coordinates/coordinate_types.h"
#include "gameengine/entities/animatable.h"
#include "gameengine/render/renderer.h"

class GameEngine;

class Label : public Animatable, public Renderer {
 public:
  Label(GameEngine &game_engine, GamePoint position);

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
