//
//  AnalyticsEngineIOS.mm
//  GameEngine
//
//  Created by Jon Sharkey on 3/5/13.
//
//

#import "ios/thirdparty/Flurry iPhone SDK v4.1.0/Flurry/Flurry.h"
#include "ios/AnalyticsEngineIOS.h"
#include "ios/TypeUtil.h"


// AnalyticsEngine

void AnalyticsEngineIOS::LogEvent(string event_name) {
  NSString *event_name_nsstring = TypeUtil::string2NSString(event_name);
  [Flurry logEvent:event_name_nsstring];
}

void AnalyticsEngineIOS::LogEvent(string event_name, map<string, string> parameters) {
  NSString *event_name_nsstring = TypeUtil::string2NSString(event_name);
  NSMutableDictionary *parameters_nsdictionary =
      [NSMutableDictionary dictionaryWithCapacity:parameters.size()];
  for (map<string, string>::iterator i = parameters.begin(); i != parameters.end(); i++) {
    NSString *key = TypeUtil::string2NSString(i->first);
    NSString *value = TypeUtil::string2NSString(i->second);
    [parameters_nsdictionary setValue:value forKey:key];
  }

  [Flurry logEvent:event_name_nsstring withParameters:parameters_nsdictionary];
}
