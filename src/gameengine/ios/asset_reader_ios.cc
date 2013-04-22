//
//  asset_reader_ios.cc
//  GameEngine
//
//  Created by Jon Sharkey on 2013-04-22.
//  Copyright 2013 Sharkable. All rights reserved.
//

#include "gameengine/ios/asset_reader_ios.h"

#include <sys/stat.h>

AssetReaderIOS::AssetReaderIOS(std::string filename)
    : filename_(filename),
      file_size_(-1) {
  file_ptr_ = fopen(filename.c_str(), "rb");
}

AssetReaderIOS::~AssetReaderIOS() {
  if (file_ptr_) {
    fclose(file_ptr_);
  }
}

size_t AssetReaderIOS::size() {
  if (file_size_ == -1) {
    struct stat file_stat;
    stat(filename_.c_str(), &file_stat);
    file_size_ = file_stat.st_size;
  }
  return file_size_;
}

size_t AssetReaderIOS::read(void *ptr, size_t size, size_t count) {
  if (file_ptr_) {
    return fread(ptr, size, count, file_ptr_);
  }
  return 0;
}

bool AssetReaderIOS::close() {
  if (file_ptr_) {
    bool result = fclose(file_ptr_);
    file_ptr_ = NULL;
    return result;
  }
  return false;
}
