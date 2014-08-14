//
//  asset_reader_factory_module.h
//  SharkEngine
//
//  Created by Jon Sharkey on 2013-04-19.
//  Copyright 2013 Sharkable. All rights reserved.
//

#ifndef SHARKENGINE_MODULES_ASSETREADERFACTORYMODULE_H_
#define SHARKENGINE_MODULES_ASSETREADERFACTORYMODULE_H_

#include <string>

#include "sharkengine/module.h"

class AssetReader;

class AssetReaderFactoryModule : Module {
 public:
  virtual AssetReader * CreateAssetReader(std::string filename) = 0;
};

#endif
