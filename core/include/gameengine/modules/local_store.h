//
//  local_store.h
//  GameEngine
//
//  Created by Jon Sharkey on 2010-05-02.
//  Copyright 2010 Sharkable. All rights reserved.
//

#ifndef GAMEENGINE_LOCALSTORE_H_
#define GAMEENGINE_LOCALSTORE_H_

#include <string>

class LocalStore {
 public:
  virtual bool HasEntryForKey(std::string key) = 0;
  virtual bool BoolForKey(std::string key) = 0;
  virtual void SetBool(bool value, std::string key) = 0;
  virtual int IntegerForKey(std::string key) = 0;
  virtual void SetInteger(int value, std::string key) = 0;
  virtual double DoubleForKey(std::string key) = 0;
  virtual void SetDouble(double value, std::string key) = 0;
  virtual std::string StringForKey(std::string key) = 0;
  virtual void SetString(std::string value, std::string key) = 0;
};

#endif
