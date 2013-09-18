//
//  android_asset_reader_factory_module.h
//  GameEngine
//
//  Created by Jon Sharkey on 2013-04-19.
//  Copyright 2013 Sharkable. All rights reserved.
//

#ifndef GAMEENGINE_ANDROID_MODULES_ANDROIDASSETREADERFACTORYMODULE_H_
#define GAMEENGINE_ANDROID_MODULES_ANDROIDASSETREADERFACTORYMODULE_H_

#include <string>

#include "gameengine/modules/asset_reader_factory_module.h"

class AndroidAssetReaderFactoryModule : public AssetReaderFactoryModule {
 public:
  // Module
  bool IsImplemented() { return true; };

  // AssetReaderFactoryModule
  sp<AssetReader> CreateAssetReader(std::string filename);
};

#endif