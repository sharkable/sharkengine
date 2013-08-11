//
//  input_module.h
//  GameEngine
//
//  Created by Jon Sharkey on 2012-08-11.
//  Copyright 2012 Sharkable. All rights reserved.
//

#ifndef GAMEENGINE_INPUTMODULE_H_
#define GAMEENGINE_INPUTMODULE_H_

#include "gameengine/module.h"

class InputModule : public Module {
 public:
  virtual void HidePointer() {};
  virtual void ShowPointer() {};
};

#endif
