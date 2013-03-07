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

@class NSString;

class TypeUtil {
 public:
  static std::string NSString2string(NSString *string);
  static NSString *string2NSString(std::string string);
};

#endif
