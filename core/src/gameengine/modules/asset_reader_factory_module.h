//
//  asset_reader_factory_module.h
//  SharkEngine
//
//  Created by Jon Sharkey on 2013-04-19.
//  Copyright 2013 Sharkable. All rights reserved.
//

#ifndef GAMEENGINE_MODULES_ASSETREADERFACTORYMODULE_H_
#define GAMEENGINE_MODULES_ASSETREADERFACTORYMODULE_H_

#include <string>

#include "gameengine/module.h"

class AssetReader;

class AssetReaderFactoryModule : Module {
 public:
  virtual AssetReader * CreateAssetReader(std::string filename) = 0;
};

#endif
