//
//  IOSAssetReaderFactoryModule.mm
//  SharkEngine
//
//  Created by Jon Sharkey on 2013-04-22.
//  Copyright 2013 Sharkable. All rights reserved.
//

#include "sharkengine/apple/modules/ios/IOSAssetReaderFactoryModule.h"

#include "sharkengine/apple/ios/IOSAssetReader.h"

using std::string;

// AssetReaderFactoryModule

AssetReader * IOSAssetReaderFactoryModule::CreateAssetReader(std::string filename) {
  return new IOSAssetReader(filename);
}
