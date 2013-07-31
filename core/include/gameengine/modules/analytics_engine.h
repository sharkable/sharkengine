//
//  analytics_engine.h
//  GameEngine
//
//  Created by Jon Sharkey on 2013-03-05.
//  Copyright 2013 Sharkable. All rights reserved.
//

#ifndef GAMEENGINE_ANALYITICSENGINE_H_
#define GAMEENGINE_ANALYITICSENGINE_H_

#include "gameengine/module.h"

struct ScreenPoint;

class AnalyticsEngine : public Module {
 public:
  virtual void LogEvent(std::string event_name) {};
  virtual void LogEvent(std::string event_name, std::map<std::string, std::string> parameters) {};
};

#endif
