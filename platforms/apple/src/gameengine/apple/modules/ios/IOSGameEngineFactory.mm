//
//  AppleGameEngineFactory.mm
//  GameEngine
//
//  Created by Jon Sharkey on 2013-04-22.
//  Copyright 2013 Sharkable. All rights reserved.
//

#include "gameengine/apple/modules/AppleGameEngineFactory.h"

#include "gameengine/apple/modules/AppleAssetReader.h"

using std::string;

sp<AssetReader> AppleGameEngineFactory::createAssetReader(std::string filename) {
  return sp<AssetReader>(new AppleAssetReader(filename));
}
