//
//  android_game_engine_factory.cc
//  GameEngine
//
//  Created by Jon Sharkey on 2013-04-19.
//  Copyright 2013 Sharkable. All rights reserved.
//

#include "gameengine/android/modules/android_game_engine_factory.h"

#include "gameengine/android/modules/android_asset_reader.h"

using std::string;

sp<AssetReader> AndroidGameEngineFactory::createAssetReader(std::string filename) {
  return sp<AssetReader>(new AndroidAssetReader(filename));
}
