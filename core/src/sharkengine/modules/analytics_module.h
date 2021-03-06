//
//  analytics_module.h
//  SharkEngine
//
//  Created by Jon Sharkey on 2013-03-05.
//  Copyright 2013 Sharkable. All rights reserved.
//

#ifndef SHARKENGINE_ANALYITICSMODULE_H_
#define SHARKENGINE_ANALYITICSMODULE_H_

#include "sharkengine/module.h"

struct ScreenPoint;

class AnalyticsModule : public Module {
 public:
  virtual void LogEvent(std::string event_name) {};
  virtual void LogEvent(std::string event_name, std::map<std::string, std::string> parameters) {};
};

#endif
