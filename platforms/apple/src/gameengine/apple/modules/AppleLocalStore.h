//
//  AppleLocalStore.h
//  GameEngine
//
//  Created by Jon Sharkey on 2013-05-15.
//  Copyright 2013 Sharkable. All rights reserved.
//

#ifndef GAMEENGINE_IOS_APPLELOCALSTORE_H_
#define GAMEENGINE_IOS_APPLELOCALSTORE_H_

#include <string>

#include "gameengine/modules/local_store.h"

class AppleLocalStore : public LocalStore {
 public:
  // LocalStore
  bool HasEntryForKey(std::string key);
  bool BoolForKey(std::string key);
  void SetBool(bool value, std::string key);
  int IntegerForKey(std::string key);
  void SetInteger(int value, std::string key);
  double DoubleForKey(std::string key);
  void SetDouble(double value, std::string key);
  std::string StringForKey(std::string key);
  void SetString(std::string value, std::string key);

  // Module
  bool IsImplemented() { return true; };
};

#endif
