//
//  OSXGameEngineFactory.mm
//  GameEngine
//
//  Created by Jon Sharkey on 2013-08-11.
//  Copyright 2013 Sharkable. All rights reserved.
//

#include "gameengine/apple/modules/AppleGameEngineFactory.h"

#include "gameengine/apple/modules/osx/OSXGameEngineFactory.h"
#include "gameengine/modules/zipped_asset_reader.h"

using std::string;

OSXGameEngineFactory::OSXGameEngineFactory() :
    zip_(NULL) {
}

OSXGameEngineFactory::~OSXGameEngineFactory() {
  zip_close(zip_);
}

sp<AssetReader> OSXGameEngineFactory::createAssetReader(std::string filename) {
  if (!zip_) {
    NSString *path = [[NSBundle mainBundle] pathForResource:@"asset_bundle" ofType:@""];
    zip_ = zip_open([path UTF8String], 0, NULL);
    assert(zip_);
  }

  return sp<AssetReader>(new ZippedAssetReader(zip_, filename));
}
