//
//  ApplePersistenceModule.mm
//  SharkEngine
//
//  Created by Jon Sharkey on 2010-05-02.
//  Copyright 2010 Sharkable. All rights reserved.
//

#include "gameengine/apple/modules/ApplePersistenceModule.h"

#include "gameengine/apple/TypeUtil.h"

using std::string;

bool ApplePersistenceModule::HasEntryForKey(string key) {
  NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];
  return [[[userDefaults dictionaryRepresentation] allKeys]
          containsObject:TypeUtil::string2NSString(key)];
}

bool ApplePersistenceModule::BoolForKey(string key) {
  NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];
  return [userDefaults boolForKey:TypeUtil::string2NSString(key)];
}

void ApplePersistenceModule::SetBool(bool value, string key) {
  NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];
  [userDefaults setBool:value forKey:TypeUtil::string2NSString(key)];
  [userDefaults synchronize];
}

int ApplePersistenceModule::IntegerForKey(string key) {
  NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];
  return (int)[userDefaults integerForKey:TypeUtil::string2NSString(key)];
}

void ApplePersistenceModule::SetInteger(int value, string key) {
  NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];
  [userDefaults setInteger:value forKey:TypeUtil::string2NSString(key)];
  [userDefaults synchronize];
}

double ApplePersistenceModule::DoubleForKey(string key) {
  NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];
  return [userDefaults doubleForKey:TypeUtil::string2NSString(key)];
}

void ApplePersistenceModule::SetDouble(double value, string key) {
  NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];
  [userDefaults setDouble:value forKey:TypeUtil::string2NSString(key)];
  [userDefaults synchronize];
}

string ApplePersistenceModule::StringForKey(string key) {
  NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];
  NSString *value = [userDefaults stringForKey:TypeUtil::string2NSString(key)];
  return TypeUtil::NSString2string(value);
}

void ApplePersistenceModule::SetString(string value, string key) {
  NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];
  NSString *valueObjc =
      [userDefaults stringForKey:TypeUtil::string2NSString(value)];
  [userDefaults setObject:valueObjc forKey:TypeUtil::string2NSString(key)];
  [userDefaults synchronize];
}
