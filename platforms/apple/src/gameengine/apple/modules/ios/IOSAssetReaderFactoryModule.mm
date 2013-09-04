//
//  IOSModuleFactory.mm
//  GameEngine
//
//  Created by Jon Sharkey on 2013-04-22.
//  Copyright 2013 Sharkable. All rights reserved.
//

#include "gameengine/apple/modules/ios/IOSModuleFactory.h"

#include "gameengine/apple/modules/ios/IOSAssetReader.h"

using std::string;

// ModuleFactory

sp<AssetReader> IOSModuleFactory::CreateAssetReader(std::string filename) {
  return sp<AssetReader>(new IOSAssetReader(filename));
}
