//
//  android_asset_reader_factory_module.h
//  SharkEngine
//
//  Created by Jon Sharkey on 2013-04-19.
//  Copyright 2013 Sharkable. All rights reserved.
//

#ifndef SHARKENGINE_ANDROID_MODULES_ANDROIDASSETREADERFACTORYMODULE_H_
#define SHARKENGINE_ANDROID_MODULES_ANDROIDASSETREADERFACTORYMODULE_H_

#include <string>

#include "sharkengine/modules/asset_reader_factory_module.h"

class AndroidAssetReaderFactoryModule : public AssetReaderFactoryModule {
 public:
  // Module
  bool IsImplemented() { return true; };

  // AssetReaderFactoryModule
  AssetReader * CreateAssetReader(std::string filename);
};

#endif
