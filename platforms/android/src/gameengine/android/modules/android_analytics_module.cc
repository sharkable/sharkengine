//
//  android_analytics_engine.cc
//  GameEngine
//
//  Created by Jon Sharkey on 2013-04-16.
//  Copyright 2013 Sharkable. All rights reserved.
//

#include "gameengine/android/modules/android_analytics_engine.h"

using std::map;
using std::string;

AndroidAnalyticsEngine::AndroidAnalyticsEngine(JNIEnv *jni_env)
  : jni_env_(jni_env) {
  java_class_ = jni_env_->FindClass("com/sharkable/sharkengine/modules/AnalyticsEngineAndroid");
  assert(java_class_);
  begin_log_event_ = jni_env_->GetStaticMethodID(java_class_, "beginLogEvent",
                                                 "(Ljava/lang/String;)V");
  add_parameter_ = jni_env_->GetStaticMethodID(java_class_, "addParameter",
                                              "(Ljava/lang/String;Ljava/lang/String;)V");
  commit_log_event_ = jni_env_->GetStaticMethodID(java_class_, "commitLogEvent", "()V");
  assert(begin_log_event_);
  assert(add_parameter_);
  assert(commit_log_event_);
}


// AnalyticsEngine

void AndroidAnalyticsEngine::LogEvent(string event_name) {
  java_class_ = jni_env_->FindClass("com/sharkable/sharkengine/modules/AnalyticsEngineAndroid");
  jstring java_event_name = jni_env_->NewStringUTF(event_name.c_str());
  jni_env_->CallStaticVoidMethod(java_class_, begin_log_event_, java_event_name);
  jni_env_->DeleteLocalRef(java_event_name);

  jni_env_->CallStaticVoidMethod(java_class_, commit_log_event_);
}

void AndroidAnalyticsEngine::LogEvent(string event_name, map<string, string> parameters) {
  java_class_ = jni_env_->FindClass("com/sharkable/sharkengine/modules/AnalyticsEngineAndroid");
  jstring java_event_name = jni_env_->NewStringUTF(event_name.c_str());
  jni_env_->CallStaticVoidMethod(java_class_, begin_log_event_, java_event_name);
  jni_env_->DeleteLocalRef(java_event_name);

  for (auto i = parameters.begin(); i != parameters.end(); i++) {
    jstring java_key = jni_env_->NewStringUTF(i->first.c_str());
    jstring java_value = jni_env_->NewStringUTF(i->second.c_str());
    jni_env_->CallStaticVoidMethod(java_class_, add_parameter_, java_key, java_value);
    jni_env_->DeleteLocalRef(java_key);
    jni_env_->DeleteLocalRef(java_value);
  }

  jni_env_->CallStaticVoidMethod(java_class_, commit_log_event_);    
}
