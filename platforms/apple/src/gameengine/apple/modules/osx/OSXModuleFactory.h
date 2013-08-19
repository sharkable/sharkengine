//
//  OSXModuleFactory.h
//  GameEngine
//
//  Created by Jon Sharkey on 2013-08-11.
//  Copyright 2013 Sharkable. All rights reserved.
//

#ifndef GAMEENGINE_APPLE_MODULES_OSX_OSXMODULEFACTORY_H_
#define GAMEENGINE_APPLE_MODULES_OSX_OSXMODULEFACTORY_H_

#include <string>

#include "gameengine/modules/module_factory.h"

#include "zip.h"

class OSXModuleFactory : public ModuleFactory {
 public:
  OSXModuleFactory();
  ~OSXModuleFactory();

  // ModuleFactory
  sp<AssetReader> CreateAssetReader(std::string filename);

 private:
  zip *zip_;
};

#endif
