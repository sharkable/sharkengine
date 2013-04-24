//
//  TypeUtil.h
//  GameEngine
//
//  Created by Jon Sharkey on 2012-03-08.
//  Copyright 2012 Sharkable. All rights reserved.
//

#ifndef GAMEENGINE_IOS_TYPEUTIL_H_
#define GAMEENGINE_IOS_TYPEUTIL_H_

#include <string>

@class NSString;

class TypeUtil {
 public:
  static std::string NSString2string(NSString *string);
  static NSString *string2NSString(std::string string);
};

#endif
