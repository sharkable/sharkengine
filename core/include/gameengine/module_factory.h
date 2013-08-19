//
//  module_factory.h
//  GameEngine
//
//  Created by Jon Sharkey on 2013-04-19.
//  Copyright 2013 Sharkable. All rights reserved.
//

#ifndef GAMEENGINE_MODULEFACTORY_H_
#define GAMEENGINE_MODILEFACTORY_H_

#include <string>

class AssetReader;

class ModuleFactory {
 public:
  virtual sp<AssetReader> createAssetReader(std::string filename) = 0;
};

#endif
