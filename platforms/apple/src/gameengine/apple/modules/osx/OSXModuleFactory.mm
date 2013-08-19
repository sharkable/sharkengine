//
//  OSXModuleFactory.mm
//  GameEngine
//
//  Created by Jon Sharkey on 2013-08-11.
//  Copyright 2013 Sharkable. All rights reserved.
//

#include "gameengine/apple/modules/osx/OSXModuleFactory.h"

#include "gameengine/modules/zipped_asset_reader.h"

using std::string;

OSXModuleFactory::OSXModuleFactory() :
    zip_(NULL) {
}

OSXModuleFactory::~OSXModuleFactory() {
  zip_close(zip_);
}


// ModuleFactory

sp<AssetReader> OSXModuleFactory::CreateAssetReader(std::string filename) {
  if (!zip_) {
    NSString *path = [[NSBundle mainBundle] pathForResource:@"asset_bundle" ofType:@""];
    zip_ = zip_open([path UTF8String], 0, NULL);
    assert(zip_);
  }

  return sp<AssetReader>(new ZippedAssetReader(zip_, filename));
}
