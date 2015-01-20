//
//  IOSAnalyticsModule.h
//  SharkEngine
//
//  Created by Jon Sharkey on 2013-03-05.
//  Copyright 2013 Sharkable. All rights reserved.
//

#ifndef SHARKENGINE_APPLE_MODULES_IOS_IOSANALYTICSMODULE_H_
#define SHARKENGINE_APPLE_MODULES_IOS_IOSANALYTICSMODULE_H_

#import <map>
#import <string>

#import "sharkengine/modules/analytics_module.h"

// TODO have this do setup as well maybe?
class IOSAnalyticsModule : public AnalyticsModule {
 public:
  // AnalyticsModule
  void LogEvent(std::string event_name);
  void LogEvent(std::string event_name, std::map<std::string, std::string> parameters);

  // Module
  bool IsImplemented() { return true; };
};

#endif
