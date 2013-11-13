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

#include "gameengine/coordinate_types.h"
#include "gameengine/entities/animatable.h"

class GameEngine;

class Label : public Animatable {
 public:
  Label(GameEngine &game_engine, GamePoint position);

  const std::string & Text();
  void SetText(const std::string &text);

  // ViewEntity
  void Render(GamePoint offset);
  void Render(GamePoint offset, float angle);
  GameRect Rect();

 private:
  GameSize CalculateSize();

  std::string text_;
  GameSize size_;
};

#endif
