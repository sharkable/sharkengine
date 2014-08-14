//
//  android_asset_reader.h
//  SharkEngine
//
//  Created by Jon Sharkey on 2013-04-19.
//  Copyright 2013 Sharkable. All rights reserved.
//

#ifndef SHARKENGINE_ANDROID_ANDROIDASSETREADER_H_
#define SHARKENGINE_ANDROID_ANDROIDASSETREADER_H_

#include <string>

#include "gameengine/asset_reader.h"

struct zip_file;

class AndroidAssetReader : public AssetReader {
 public:
  AndroidAssetReader(std::string filename);
  ~AndroidAssetReader();
  size_t Size();
  size_t Read(void *ptr, size_t size, size_t count);
  bool Close();
  bool IsOpen();

 private:
  std::string filename_;
  zip_file *file_ptr_;
  size_t file_size_;
};

#endif
