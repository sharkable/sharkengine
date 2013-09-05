//
//  android_asset_reader_factory_module.cc
//  GameEngine
//
//  Created by Jon Sharkey on 2013-04-19.
//  Copyright 2013 Sharkable. All rights reserved.
//

#include "gameengine/android/modules/android_asset_reader_factory_module.h"

#include "gameengine/android/modules/android_asset_reader.h"

using std::string;

// AssetReaderFactoryModule

sp<AssetReader> AndroidAssetReaderFactoryModule::CreateAssetReader(std::string filename) {
  return sp<AssetReader>(new AndroidAssetReader(filename));
}
