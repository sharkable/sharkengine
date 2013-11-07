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

class Label : public Animatable {
 public:
  Label(GameEngine &game_engine, GamePoint position);

  const std::string & text() { return text_; }
  void set_text(const std::string &text) { text_ = text; }

  // ViewEntity
  void Render(GamePoint offset);

 private:
  std::string text_;
};

#endif
