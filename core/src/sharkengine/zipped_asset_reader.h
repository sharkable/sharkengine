//
//  zipped_asset_reader.h
//  SharkEngine
//
//  Created by Jon Sharkey on 2013-04-19.
//  Copyright 2013 Sharkable. All rights reserved.
//

#ifndef SHARKENGINE_MODULES_ZIPPEDASSETREADER_H_
#define SHARKENGINE_MODULES_ZIPPEDASSETREADER_H_

#include <string>

#include "sharkengine/asset_reader.h"

struct zip;
struct zip_file;

class ZippedAssetReader : public AssetReader {
 public:
  ZippedAssetReader(zip *zip, std::string filename);
  ~ZippedAssetReader();
  size_t Size();
  size_t Read(void *ptr, size_t size, size_t count);
  bool Close();
  bool IsOpen();

 private:
  std::string filename_;
  zip *zip_;  // weak
  zip_file *zip_file_;
  size_t file_size_;
};

#endif
