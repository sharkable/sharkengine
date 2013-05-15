//
//  LocalStoreIOS.m
//  GameEngine
//
//  Created by Jon Sharkey on 2010-05-02.
//  Copyright 2010 Sharkable. All rights reserved.
//

#include "gameengine/ios/LocalStoreIOS.h"

#include "gameengine/ios/TypeUtil.h"

using std::string;

bool LocalStoreIOS::HasEntryForKey(string key) {
  NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];
  return [[[userDefaults dictionaryRepresentation] allKeys]
          containsObject:TypeUtil::string2NSString(key)];
}

bool LocalStoreIOS::BoolForKey(string key) {
  NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];
  return [userDefaults boolForKey:TypeUtil::string2NSString(key)];
}

void LocalStoreIOS::SetBool(bool value, string key) {
  NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];
  [userDefaults setBool:value forKey:TypeUtil::string2NSString(key)];
  [userDefaults synchronize];
}

int LocalStoreIOS::IntegerForKey(string key) {
  NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];
  return [userDefaults integerForKey:TypeUtil::string2NSString(key)];
}

void LocalStoreIOS::SetInteger(int value, string key) {
  NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];
  [userDefaults setInteger:value forKey:TypeUtil::string2NSString(key)];
  [userDefaults synchronize];
}

double LocalStoreIOS::DoubleForKey(string key) {
  NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];
  return [userDefaults doubleForKey:TypeUtil::string2NSString(key)];
}

void LocalStoreIOS::SetDouble(double value, string key) {
  NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];
  [userDefaults setDouble:value forKey:TypeUtil::string2NSString(key)];
  [userDefaults synchronize];
}

string LocalStoreIOS::StringForKey(string key) {
  NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];
  NSString *value = [userDefaults stringForKey:TypeUtil::string2NSString(key)];
  return TypeUtil::NSString2string(value);
}

void LocalStoreIOS::SetString(string value, string key) {
  NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];
  NSString *valueObjc =
      [userDefaults stringForKey:TypeUtil::string2NSString(value)];
  [userDefaults setObject:valueObjc forKey:TypeUtil::string2NSString(key)];
  [userDefaults synchronize];
}
