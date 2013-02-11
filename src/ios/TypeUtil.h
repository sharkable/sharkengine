//
//  TypeUtil.h
//  AirHockey
//
//  Created by Jon Sharkey on 3/8/12.
//  Copyright (c) 2012 Sharkable. All rights reserved.
//

#ifndef AirHockey_TypeUtil_h
#define AirHockey_TypeUtil_h

#include <string>
using namespace std;

@class NSString;

class TypeUtil {
 public:
  static string NSString2string(NSString *string);
  static NSString *string2NSString(string string);
};

#endif
