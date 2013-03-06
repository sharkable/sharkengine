//
//  analytics_engine.h
//  AirHockey
//
//  Created by Jonathan Sharkey on 3/5/13.
//  Copyright (c) 2013 Sharkable. All rights reserved.
//

#ifndef GAMEENGINE_ANALYITICSENGINE_H_
#define GAMEENGINE_ANALYITICSENGINE_H_

struct ScreenPoint;

class AnalyticsEngine {
 public:
  virtual void LogEvent(string event_name) = 0;
  virtual void LogEvent(string event_name, map<string, string> parameters) = 0;
};

#endif