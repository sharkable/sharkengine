//
//  IOSAssetReader.mm
//  SharkEngine
//
//  Created by Jon Sharkey on 2013-04-22.
//  Copyright 2013 Sharkable. All rights reserved.
//

#include "gameengine/apple/ios/IOSAssetReader.h"

#include "gameengine/apple/TypeUtil.h"

#include <sys/stat.h>

IOSAssetReader::IOSAssetReader(std::string filename) : file_size_(-1) {
  NSString *filename_nsstring = TypeUtil::string2NSString(filename);
  NSString *filename_prefix = [[filename_nsstring lastPathComponent] stringByDeletingPathExtension];
  NSString *extension = [filename_nsstring pathExtension];
  NSString *file_path = [[NSBundle mainBundle] pathForResource:filename_prefix ofType:extension];

  filename_ = [file_path retain];
  file_ptr_ = fopen(file_path.UTF8String, "rb");
}

IOSAssetReader::~IOSAssetReader() {
  [filename_ release];
  if (file_ptr_) {
    fclose(file_ptr_);
  }
}

size_t IOSAssetReader::Size() {
  if (file_size_ == -1) {
    struct stat file_stat;
    stat(filename_.UTF8String, &file_stat);
    file_size_ = file_stat.st_size;
  }
  return file_size_;
}

size_t IOSAssetReader::Read(void *ptr, size_t size, size_t count) {
  if (file_ptr_) {
    return fread(ptr, size, count, file_ptr_);
  }
  return 0;
}

bool IOSAssetReader::Close() {
  if (file_ptr_) {
    bool result = fclose(file_ptr_);
    file_ptr_ = NULL;
    return result;
  }
  return false;
}

bool IOSAssetReader::IsOpen() {
  return file_ptr_ != NULL;
}
