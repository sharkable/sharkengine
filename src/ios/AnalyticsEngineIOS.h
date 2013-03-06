//
//  AnalyticsEngineIOS.h
//  GameEngine
//
//  Created by Jon Sharkey on 3/5/13.
//
//

#ifndef GAMEENGINE_IOS_ANALYTICSENGINEIOS_H_
#define GAMEENGINE_IOS_ANALYTICSENGINEIOS_H_

#include <map>
using namespace std;

#include "gameengine/analytics_engine.h"

// TODO have this do setup as well maybe?
class AnalyticsEngineIOS : public AnalyticsEngine {
 public:
  // AnalyticsEngine
  void LogEvent(string event_name);
  void LogEvent(string event_name, map<string, string> parameters);
};

#endif  
