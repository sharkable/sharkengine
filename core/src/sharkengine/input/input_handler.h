//
//  input_handler.h
//  SharkEngine
//
//  Created by Jon Sharkey on 2013-12-19.
//  Copyright 2013 Sharkable. All rights reserved.
//

#ifndef SHARKENGINE_INPUT_INPUTHANDLER_H_
#define SHARKENGINE_INPUT_INPUTHANDLER_H_

#include "sharkengine/coordinates/coordinate_system.h"
#include "sharkengine/input/input_event.h"

class InputHandler {
 public:
  virtual ~InputHandler() {}
  virtual bool HandleInputEvent(InputEvent const &event,
                                CoordinateSystem const &coordinate_system) = 0;
};

#endif
