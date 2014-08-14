//
//  OSXAssetReaderFactoryModule.mm
//  SharkEngine
//
//  Created by Jon Sharkey on 2013-08-11.
//  Copyright 2013 Sharkable. All rights reserved.
//

#include "gameengine/apple/modules/osx/OSXAssetReaderFactoryModule.h"

#include "gameengine/zipped_asset_reader.h"

using std::string;

OSXAssetReaderFactoryModule::OSXAssetReaderFactoryModule() :
    zip_(NULL) {
}

OSXAssetReaderFactoryModule::~OSXAssetReaderFactoryModule() {
  zip_close(zip_);
}


#pragma mark - AssetReaderFactoryModule

AssetReader * OSXAssetReaderFactoryModule::CreateAssetReader(std::string filename) {
  if (!zip_) {
    NSString *path = [[NSBundle mainBundle] pathForResource:@"asset_bundle" ofType:@""];
    zip_ = zip_open([path UTF8String], 0, NULL);
    assert(zip_);
  }

  return new ZippedAssetReader(zip_, filename);
}
