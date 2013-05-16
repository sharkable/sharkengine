//
//  LocalStoreAndroid.h
//  GameEngine
//
//  Created by Jon Sharkey on 2013-05-15.
//  Copyright 2013 Sharkable. All rights reserved.
//

#ifndef GAMEENGINE_IOS_LOCALSTOREANDROID_H_
#define GAMEENGINE_IOS_LOCALSTOREANDROID_H_

#include <jni.h>
#include <string>

#include "gameengine/modules/local_store.h"

class LocalStoreAndroid : public LocalStore {
 public:
  LocalStoreAndroid(JNIEnv *jni_env, jobject java_object);
  ~LocalStoreAndroid();

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

 private:
  JNIEnv *jni_env_;
  jobject java_object_;
  jmethodID has_entry_for_key_;
  jmethodID bool_for_key_;
  jmethodID set_bool_;
  jmethodID integer_for_key_;
  jmethodID set_integer_;
  jmethodID double_for_key_;
  jmethodID set_double_;
  jmethodID string_for_key_;
  jmethodID set_string_;
};

#endif
