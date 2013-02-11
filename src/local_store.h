//
//  local_store.h
//  AirHockey
//
//  Created by Jonathan Sharkey on 10-05-02.
//  Copyright 2010 Sharkable. All rights reserved.
//

#ifndef AIRHOCKEY_GAMEENGINE_LOCALSTORE_H_
#define AIRHOCKEY_GAMEENGINE_LOCALSTORE_H_

#import <string>
using namespace std;

namespace LocalStore {

bool HasEntryForKey(string key);
bool BoolForKey(string key);
void SetBool(bool value, string key);
int IntegerForKey(string key);
void SetInteger(int value, string key);
double DoubleForKey(string key);
void SetDouble(double value, string key);
string StringForKey(string key);
void SetString(string value, string key);

}

#endif
