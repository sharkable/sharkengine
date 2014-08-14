//
//  IOSAssetReaderFactoryModule.h
//  SharkEngine
//
//  Created by Jon Sharkey on 2013-04-22.
//  Copyright 2013 Sharkable. All rights reserved.
//

#ifndef SHARKENGINE_APPLE_MODULES_IOS_IOSASSETREADERFACTORYMODULE_H_
#define SHARKENGINE_APPLE_MODULES_IOS_IOSASSETREADERFACTORYMODULE_H_

#include <string>

#include "gameengine/modules/asset_reader_factory_module.h"

class IOSAssetReaderFactoryModule : public AssetReaderFactoryModule {
 public:
  // Module
  bool IsImplemented() { return true; };

  // AssetReaderFactoryModule
  AssetReader * CreateAssetReader(std::string filename);
};

#endif
