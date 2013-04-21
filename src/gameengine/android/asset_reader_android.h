//
//  asset_reader_android.h
//  GameEngine
//
//  Created by Jon Sharkey on 2013-04-19.
//  Copyright 2013 Sharkable. All rights reserved.
//

#ifndef GAMEENGINE_ASSETREADERANDROID_H_
#define GAMEENGINE_ASSETREADERANDROID_H_

#include <string>

#include "gameengine/asset_reader.h"

struct zip_file;

class AssetReaderAndroid : public AssetReader {
 public:
  AssetReaderAndroid(std::string filename);
  ~AssetReaderAndroid();
  size_t size();
  size_t read(void *ptr, size_t size, size_t count);
  bool close();

 private:
  std::string filename_;
  zip_file *file_ptr_;
  size_t file_size_;
};

#endif
