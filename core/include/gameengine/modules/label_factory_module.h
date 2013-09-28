//
//  label_factory_module.h
//  GameEngine
//
//  Created by Jon Sharkey on 2013-09-18.
//  Copyright 2013 Sharkable. All rights reserved.
//

#ifndef GAMEENGINE_MODULES_LABELFACTORYMODULE_H_
#define GAMEENGINE_MODULES_LABELFACTORYMODULE_H_

#include <string>

#include "gameengine/coordinate_types.h"
#include "gameengine/module.h"

class Label;

class LabelFactoryModule : Module {
 public:
  virtual Label * CreateLabel(std::string text, GamePoint position) = 0;
};

#endif
