//
//  TypeUtil.cpp
//  AirHockey
//
//  Created by Jon Sharkey on 3/8/12.
//  Copyright (c) 2012 Sharkable. All rights reserved.
//

#import "TypeUtil.h"

#import <Foundation/Foundation.h>

using std::string;

string TypeUtil::NSString2string(NSString *str) {
  return string([str UTF8String]);
}

NSString *TypeUtil::string2NSString(string str) {
  return [NSString stringWithUTF8String:str.c_str()];
}
