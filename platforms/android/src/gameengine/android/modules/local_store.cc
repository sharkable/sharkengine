//
//  LocalStore.m
//  GameEngine
//
//  Created by Jon Sharkey on 2010-05-02.
//  Copyright 2010 Sharkable. All rights reserved.
//

#include "gameengine/modules/local_store.h"

using std::string;

bool LocalStore::HasEntryForKey(string key) {
  return false;
}

bool LocalStore::BoolForKey(string key) {
  return false;
}

void LocalStore::SetBool(bool value, string key) {
}

int LocalStore::IntegerForKey(string key) {
  return 0;
}

void LocalStore::SetInteger(int value, string key) {
}

double LocalStore::DoubleForKey(string key) {
  return 0;
}

void LocalStore::SetDouble(double value, string key) {
}

string LocalStore::StringForKey(string key) {
  return string();
}

void LocalStore::SetString(string value, string key) {
}
