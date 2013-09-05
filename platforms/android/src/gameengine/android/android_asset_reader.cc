//
//  android_asset_reader.cc
//  GameEngine
//
//  Created by Jon Sharkey on 2013-04-19.
//  Copyright 2013 Sharkable. All rights reserved.
//

#include "gameengine/android/modules/android_asset_reader.h"
#include "gameengine/thirdparty/libzip/zip.h"

// TODO UGH this is kinda gross. This is needed for the GLOBAL variable APKArchive.
#include "jni/app.h"

AndroidAssetReader::AndroidAssetReader(std::string filename)
    : filename_(filename),
      file_size_(-1) {
  file_ptr_ = zip_fopen(APKArchive, filename.c_str(), 0);
}

AndroidAssetReader::~AndroidAssetReader() {
  if (file_ptr_) {
    zip_fclose(file_ptr_);
  }
}

size_t AndroidAssetReader::Size() {
  if (file_size_ == -1) {
    struct zip_stat stat;
    zip_stat(APKArchive, filename_.c_str(), 0, &stat);
    file_size_ = stat.size;
  }
  return file_size_;
}

size_t AndroidAssetReader::Read(void *ptr, size_t size, size_t count) {
  if (file_ptr_) {
    return zip_fread(file_ptr_, ptr, size * count);
  }
  return 0;
}

bool AndroidAssetReader::Close() {
  if (file_ptr_) {
    bool result = zip_fclose(file_ptr_);
    file_ptr_ = NULL;
    return result;
  }
  return false;
}

bool AndroidAssetReader::IsOpen() {
  return file_ptr_ != NULL;
}
