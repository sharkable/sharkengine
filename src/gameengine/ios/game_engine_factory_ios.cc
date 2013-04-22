//
//  game_engine_factory_ios.cc
//  GameEngine
//
//  Created by Jon Sharkey on 2013-04-22.
//  Copyright 2013 Sharkable. All rights reserved.
//

#include "gameengine/ios/game_engine_factory_ios.h"

#include "gameengine/ios/asset_reader_ios.h"

using std::string;

sp<AssetReader> GameEngineFactoryIOS::createAssetReader(std::string filename) {
  return sp<AssetReader>(new AssetReaderIOS(filename));
}
