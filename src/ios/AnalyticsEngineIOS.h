//
//  AnalyticsEngineIOS.h
//  GameEngine
//
//  Created by Jon Sharkey on 2013-03-05.
//  Copyright 2013 Sharkable. All rights reserved.
//

#ifndef GAMEENGINE_IOS_ANALYTICSENGINEIOS_H_
#define GAMEENGINE_IOS_ANALYTICSENGINEIOS_H_

#include <map>

#include "gameengine/analytics_engine.h"

// TODO have this do setup as well maybe?
class AnalyticsEngineIOS : public AnalyticsEngine {
 public:
  // AnalyticsEngine
  void LogEvent(std::string event_name);
  void LogEvent(std::string event_name, std::map<std::string, std::string> parameters);
};

#endif  
