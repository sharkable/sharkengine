//
//  OSXInputModule.h
//  SharkEngine
//
//  Created by Jon Sharkey on 2013-08-11.
//  Copyright 2013 Sharkable. All rights reserved.
//

#ifndef GAMEENGINE_APPLE_MODULES_OSX_OSXINPUTMODULE_H_
#define GAMEENGINE_APPLE_MODULES_OSX_OSXINPUTMODULE_H_

#include "gameengine/modules/input_module.h"

class OSXInputModule : public InputModule {
 public:
  // InputModule
  void HidePointer();
  void ShowPointer();
};

#endif
