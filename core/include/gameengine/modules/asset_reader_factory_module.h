//
//  asset_reader_factory_module.h
//  GameEngine
//
//  Created by Jon Sharkey on 2013-04-19.
//  Copyright 2013 Sharkable. All rights reserved.
//

#ifndef GAMEENGINE_ASSETREADERFACTORYMODULE_H_
#define GAMEENGINE_ASSETREADERFACTORYMODULE_H_

#include <string>

#include "gameengine/module.h"

class AssetReader;

class AssetReaderFactoryModule : Module {
 public:
  virtual sp<AssetReader> CreateAssetReader(std::string filename) = 0;
};

#endif
