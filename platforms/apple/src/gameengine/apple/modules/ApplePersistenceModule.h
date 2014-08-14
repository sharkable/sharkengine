//
//  ApplePersistenceModule.h
//  SharkEngine
//
//  Created by Jon Sharkey on 2013-05-15.
//  Copyright 2013 Sharkable. All rights reserved.
//

#ifndef GAMEENGINE_APPLE_MODULES_APPLEPERSISTENCEMODULE_H_
#define GAMEENGINE_APPLE_MODULES_APPLEPERSISTENCEMODULE_H_

#include <string>

#include "gameengine/modules/persistence_module.h"

class ApplePersistenceModule : public PersistenceModule {
 public:
  // PersistenceModule
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
