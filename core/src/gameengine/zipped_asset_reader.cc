//
//  zipped_asset_reader.cc
//  GameEngine
//
//  Created by Jon Sharkey on 2013-04-19.
//  Copyright 2013 Sharkable. All rights reserved.
//

#include "gameengine/zipped_asset_reader.h"

#include "gameengine/thirdparty/libzip/zip.h"

ZippedAssetReader::ZippedAssetReader(zip *zip, std::string filename)
    : zip_(zip),
      filename_(filename),
      file_size_(-1) {
  zip_file_ = zip_fopen(zip_, filename.c_str(), 0);
}

ZippedAssetReader::~ZippedAssetReader() {
  if (zip_file_) {
    zip_fclose(zip_file_);
  }
}

size_t ZippedAssetReader::Size() {
  if (file_size_ == -1) {
    struct zip_stat stat;
    zip_stat(zip_, filename_.c_str(), 0, &stat);
    file_size_ = (size_t)stat.size;  // #sharkable
  }
  return file_size_;
}

size_t ZippedAssetReader::Read(void *ptr, size_t size, size_t count) {
  if (zip_file_) {
    return zip_fread(zip_file_, ptr, size * count);
  }
  return 0;
}

bool ZippedAssetReader::Close() {
  if (zip_file_) {
    bool result = zip_fclose(zip_file_);
    zip_file_ = NULL;
    return result;
  }
  return false;
}

bool ZippedAssetReader::IsOpen() {
  return zip_file_ != NULL;
}
