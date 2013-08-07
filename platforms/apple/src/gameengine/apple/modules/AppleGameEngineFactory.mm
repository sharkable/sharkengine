//
//  GameEngineFactoryIOS.mm
//  GameEngine
//
//  Created by Jon Sharkey on 2013-04-22.
//  Copyright 2013 Sharkable. All rights reserved.
//

#include "gameengine/apple/modules/GameEngineFactoryIOS.h"

#include "gameengine/apple/modules/AssetReaderIOS.h"

using std::string;

sp<AssetReader> GameEngineFactoryIOS::createAssetReader(std::string filename) {
  return sp<AssetReader>(new AssetReaderIOS(filename));
}
