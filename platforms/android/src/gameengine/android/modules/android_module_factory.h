//
//  android_module_factory.h
//  GameEngine
//
//  Created by Jon Sharkey on 2013-04-19.
//  Copyright 2013 Sharkable. All rights reserved.
//

#ifndef GAMEENGINE_ANDROID_MODULES_ANDROIDMODULEFACTORY_H_
#define GAMEENGINE_ANDROID_MODULES_ANDROIDMODULEFACTORY_H_

#include <string>

#include "gameengine/modules/module_factory.h"

class AndroidModuleFactory : public ModuleFactory {
 public:
  sp<AssetReader> CreateAssetReader(std::string filename);
};

#endif
