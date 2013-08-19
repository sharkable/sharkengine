//
//  IOSModuleFactory.h
//  GameEngine
//
//  Created by Jon Sharkey on 2013-04-22.
//  Copyright 2013 Sharkable. All rights reserved.
//

#ifndef GAMEENGINE_APPLE_MODULES_IOS_IOSMODULEFACTORY_H_
#define GAMEENGINE_APPLE_MODULES_IOS_IOSMODULEFACTORY_H_

#include <string>

#include "gameengine/module_factory.h"

class IOSModuleFactory : public ModuleFactory {
 public:
  // ModuleFactory
  sp<AssetReader> CreateAssetReader(std::string filename);
};

#endif
