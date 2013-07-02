//
//  analytics_engine_android.h
//  GameEngine
//
//  Created by Jon Sharkey on 2013-04-16.
//  Copyright 2013 Sharkable. All rights reserved.
//

#ifndef GAMEENGINE_IOS_ANALYTICSENGINEANRDOID_H_
#define GAMEENGINE_IOS_ANALYTICSENGINEANDROID_H_

#include <jni.h>
#include <map>
#include <string>

#include "gameengine/modules/analytics_engine.h"

// TODO have this do setup as well maybe?
class AnalyticsEngineAndroid : public AnalyticsEngine {
 public:
  AnalyticsEngineAndroid(JNIEnv *jni_env);

  // AnalyticsEngine
  void LogEvent(std::string event_name);
  void LogEvent(std::string event_name, std::map<std::string, std::string> parameters);

 private:
  JNIEnv *jni_env_;
  jclass java_class_;
  jmethodID begin_log_event_;
  jmethodID add_parameter_;
  jmethodID commit_log_event_;  
};

#endif
