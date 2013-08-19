//
//  android_module_factory.cc
//  GameEngine
//
//  Created by Jon Sharkey on 2013-04-19.
//  Copyright 2013 Sharkable. All rights reserved.
//

#include "gameengine/android/modules/android_module_factory.h"

#include "gameengine/android/modules/android_asset_reader.h"

using std::string;

sp<AssetReader> AndroidModuleFactory::CreateAssetReader(std::string filename) {
  return sp<AssetReader>(new AndroidAssetReader(filename));
}
