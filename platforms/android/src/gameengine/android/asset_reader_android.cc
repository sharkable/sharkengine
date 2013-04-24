//
//  asset_reader_android.cc
//  GameEngine
//
//  Created by Jon Sharkey on 2013-04-19.
//  Copyright 2013 Sharkable. All rights reserved.
//

#include "gameengine/android/asset_reader_android.h"

// TODO This is currently in the airhockey source. Rethink JNI... and the GameEngine in general.
#include "libzip/zip.h"

// TODO UGH this is kinda gross. This is needed for the GLOBAL variable APKArchive.
#include "app.h"

AssetReaderAndroid::AssetReaderAndroid(std::string filename)
    : filename_(filename),
      file_size_(-1) {
  file_ptr_ = zip_fopen(APKArchive, filename.c_str(), 0);
}

AssetReaderAndroid::~AssetReaderAndroid() {
  if (file_ptr_) {
    zip_fclose(file_ptr_);
  }
}

size_t AssetReaderAndroid::Size() {
  if (file_size_ == -1) {
    struct zip_stat stat;
    zip_stat(APKArchive, filename_.c_str(), 0, &stat);
    file_size_ = stat.size;
  }
  return file_size_;
}

size_t AssetReaderAndroid::Read(void *ptr, size_t size, size_t count) {
  if (file_ptr_) {
    return zip_fread(file_ptr_, ptr, size * count);
  }
  return 0;
}

bool AssetReaderAndroid::Close() {
  if (file_ptr_) {
    bool result = zip_fclose(file_ptr_);
    file_ptr_ = NULL;
    return result;
  }
  return false;
}

bool AssetReaderAndroid::IsOpen() {
  return file_ptr_ != NULL;
}
