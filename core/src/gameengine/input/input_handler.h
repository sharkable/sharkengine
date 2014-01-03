//
//  input_handler.h
//  GameEngine
//
//  Created by Jon Sharkey on 12/19/2013.
//  Copyright (c) 2013 Jon Sharkey. All rights reserved.
//

#ifndef GAMEENGINE_INPUT_INPUTHANDLER_H_
#define GAMEENGINE_INPUT_INPUTHANDLER_H_

#include "gameengine/coordinates/coordinate_system.h"
#include "gameengine/input/input_event.h"

class InputHandler {
 public:
  virtual ~InputHandler() {}
  virtual bool HandleInputEvent(InputEvent const &event,
                                CoordinateSystem const &coordinate_system) = 0;
};

#endif
