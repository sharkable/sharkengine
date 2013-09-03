//
//  IOSAnalyticsEngine.mm
//  GameEngine
//
//  Created by Jon Sharkey on 2013-03-05.
//  Copyright 2013 Sharkable. All rights reserved.
//

#import "gameengine/apple/modules/ios/IOSAnalyticsEngine.h"

#import "gameengine/apple/TypeUtil.h"
#import "gameengine/apple/thirdparty/ios/flurry/Flurry.h"

using std::map;
using std::string;

// AnalyticsEngine

void IOSAnalyticsEngine::LogEvent(string event_name) {
  NSString *event_name_nsstring = TypeUtil::string2NSString(event_name);
  [Flurry logEvent:event_name_nsstring];
}

void IOSAnalyticsEngine::LogEvent(string event_name, map<string, string> parameters) {
  NSString *event_name_nsstring = TypeUtil::string2NSString(event_name);
  NSMutableDictionary *parameters_nsdictionary =
      [NSMutableDictionary dictionaryWithCapacity:parameters.size()];
  for (auto i = parameters.begin(); i != parameters.end(); i++) {
    NSString *key = TypeUtil::string2NSString(i->first);
    NSString *value = TypeUtil::string2NSString(i->second);
    [parameters_nsdictionary setValue:value forKey:key];
  }

  [Flurry logEvent:event_name_nsstring withParameters:parameters_nsdictionary];
}
