//
//  persistence_module.h
//  SharkEngine
//
//  Created by Jon Sharkey on 2010-05-02.
//  Copyright 2010 Sharkable. All rights reserved.
//

#ifndef SHARKENGINE_MODULES_PERSISTENCEMODULE_H_
#define SHARKENGINE_MODULES_PERSISTENCEMODULE_H_

#include <string>

#include "gameengine/module.h"

class PersistenceModule : public Module {
 public:
  virtual bool HasEntryForKey(std::string key) { return false; };
  virtual bool BoolForKey(std::string key) { return false; };
  virtual void SetBool(bool value, std::string key) {};
  virtual int IntegerForKey(std::string key) { return 0; };
  virtual void SetInteger(int value, std::string key) {};
  virtual double DoubleForKey(std::string key) { return 0; };
  virtual void SetDouble(double value, std::string key) {};
  virtual std::string StringForKey(std::string key) { return ""; };
  virtual void SetString(std::string value, std::string key) {};
};

#endif
