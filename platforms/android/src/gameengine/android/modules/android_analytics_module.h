//
//  android_analytics_module.h
//  GameEngine
//
//  Created by Jon Sharkey on 2013-04-16.
//  Copyright 2013 Sharkable. All rights reserved.
//

#ifndef GAMEENGINE_ANDROID_MODULES_ANDROIDANALYTICSMODULE_H_
#define GAMEENGINE_ANDROID_MODULES_ANDROIDANALYTICSMODULE_H_

#include <jni.h>
#include <map>
#include <string>

#include "gameengine/modules/analytics_module.h"

// TODO have this do setup as well maybe?
class AndroidAnalyticsModule : public AnalyticsModule {
 public:
  AndroidAnalyticsModule(JNIEnv *jni_env);

  // AnalyticsModule
  void LogEvent(std::string event_name);
  void LogEvent(std::string event_name, std::map<std::string, std::string> parameters);

  // Module
  bool IsImplemented() { return true; };

 private:
  JNIEnv *jni_env_;
  jclass java_class_;
  jmethodID begin_log_event_;
  jmethodID add_parameter_;
  jmethodID commit_log_event_;  
};

#endif
