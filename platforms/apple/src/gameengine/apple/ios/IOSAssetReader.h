//
//  IOSAssetReader.h
//  GameEngine
//
//  Created by Jon Sharkey on 2013-04-22.
//  Copyright 2013 Sharkable. All rights reserved.
//

#ifndef GAMEENGINE_APPLE_MODULES_IOS_IOSASSETREADER_H_
#define GAMEENGINE_APPLE_MODULES_IOS_IOSASSETREADER_H_

#import <Foundation/Foundation.h>

#include "gameengine/asset_reader.h"

class IOSAssetReader : public AssetReader {
 public:
  IOSAssetReader(std::string filename);
  ~IOSAssetReader();
  size_t Size();
  size_t Read(void *ptr, size_t size, size_t count);
  bool Close();
  bool IsOpen();

 private:
  NSString *filename_;
  FILE *file_ptr_;
  size_t file_size_;
};

#endif
