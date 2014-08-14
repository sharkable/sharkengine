//
//  OSXAssetReaderFactoryModule.h
//  SharkEngine
//
//  Created by Jon Sharkey on 2013-08-11.
//  Copyright 2013 Sharkable. All rights reserved.
//

#ifndef SHARKENGINE_APPLE_MODULES_OSX_OSXASSETREADERFACTORYMODULE_H_
#define SHARKENGINE_APPLE_MODULES_OSX_OSXASSETREADERFACTORYMODULE_H_

#include <string>

#include "gameengine/modules/asset_reader_factory_module.h"

#include "zip.h"

class OSXAssetReaderFactoryModule : public AssetReaderFactoryModule {
 public:
  OSXAssetReaderFactoryModule();
  ~OSXAssetReaderFactoryModule();

  // Module
  bool IsImplemented() { return true; };

  // AssetReaderFactoryModule
  AssetReader * CreateAssetReader(std::string filename);

 private:
  zip *zip_;
};

#endif
