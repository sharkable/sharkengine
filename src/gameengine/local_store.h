//
//  local_store.h
//  GameEngine
//
//  Created by Jon Sharkey on 2010-05-02.
//  Copyright 2010 Sharkable. All rights reserved.
//

#ifndef GAMEENGINE_LOCALSTORE_H_
#define GAMEENGINE_LOCALSTORE_H_

#import <string>

namespace LocalStore {

bool HasEntryForKey(std::string key);
bool BoolForKey(std::string key);
void SetBool(bool value, std::string key);
int IntegerForKey(std::string key);
void SetInteger(int value, std::string key);
double DoubleForKey(std::string key);
void SetDouble(double value, std::string key);
std::string StringForKey(std::string key);
void SetString(std::string value, std::string key);

}

#endif
