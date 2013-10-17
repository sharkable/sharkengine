//
//  OSXLabelFactoryModule.h
//  GameEngine
//
//  Created by Jon Sharkey on 2013-10-17.
//  Copyright 2013 Sharkable. All rights reserved.
//

#ifndef GAMEENGINE_APPLE_MODULES_OSX_OSXLABELFACTORYMODULE_H_
#define GAMEENGINE_APPLE_MODULES_OSX_OSXLABELFACTORYMODULE_H_

#include "gameengine/modules/label_factory_module.h"

#include <string>

#include "gameengine/coordinate_types.h"

class OSXLabelFactoryModule : public LabelFactoryModule {
public:
  OSXLabelFactoryModule();
  ~OSXLabelFactoryModule();

  // LabelFactoryModule
  Label * CreateLabel(std::string text, GamePoint position);
};

#endif
