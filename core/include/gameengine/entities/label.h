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
  Label(GamePoint position);

  virtual const std::string & Text() = 0;
  virtual void SetText(const std::string &text) = 0;
};

#endif
