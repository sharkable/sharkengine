//
//  IOSAssetReaderFactoryModule.mm
//  GameEngine
//
//  Created by Jon Sharkey on 2013-04-22.
//  Copyright 2013 Sharkable. All rights reserved.
//

#include "gameengine/apple/modules/ios/IOSAssetReaderFactoryModule.h"

#include "gameengine/apple/ios/IOSAssetReader.h"

using std::string;

// AssetReaderFactoryModule

sp<AssetReader> IOSAssetReaderFactoryModule::CreateAssetReader(std::string filename) {
  return sp<AssetReader>(new IOSAssetReader(filename));
}
