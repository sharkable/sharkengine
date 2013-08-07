//
//  game_engine_factory_android.cc
//  GameEngine
//
//  Created by Jon Sharkey on 2013-04-19.
//  Copyright 2013 Sharkable. All rights reserved.
//

#include "gameengine/android/modules/game_engine_factory_android.h"

#include "gameengine/android/modules/asset_reader_android.h"

using std::string;

sp<AssetReader> GameEngineFactoryAndroid::createAssetReader(std::string filename) {
  return sp<AssetReader>(new AssetReaderAndroid(filename));
}
