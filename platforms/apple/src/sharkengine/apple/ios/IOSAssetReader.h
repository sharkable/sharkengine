//
//  IOSAssetReader.h
//  SharkEngine
//
//  Created by Jon Sharkey on 2013-04-22.
//  Copyright 2013 Sharkable. All rights reserved.
//

#ifndef SHARKENGINE_APPLE_IOS_IOSASSETREADER_H_
#define SHARKENGINE_APPLE_IOS_IOSASSETREADER_H_

#import <Foundation/Foundation.h>

#include "sharkengine/asset_reader.h"

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
