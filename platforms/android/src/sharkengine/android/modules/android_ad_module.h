//
//  android_ad_module.h
//  SharkEngine
//
//  Created by Jon Sharkey on 2013-04-09.
//  Copyright 2013 Sharkable. All rights reserved.
//

#ifndef SHARKENGINE_ANDROID_MODULES_ANDROIDADMODULE_H_
#define SHARKENGINE_ANDROID_MODULES_ANDROIDADMODULE_H_

#include <jni.h>

#include "gameengine/modules/ad_module.h"

class AndroidAdModule : public AdModule {
 public:
  AndroidAdModule(JNIEnv *jni_env, jobject java_object);
  ~AndroidAdModule();

  // AdModule
  void SetPublisherId(std::string publisher_id);
  void SetAdAtPoint(ScreenPoint point);
  void RemoveAd();
  void PrepareFullScreenAd();
  bool ShowFullScreenAd();
  bool IsShowingFullScreenAd();

  // Module
  bool IsImplemented() { return true; };

 private:
  JNIEnv *jni_env_;
  jobject java_object_;
  jmethodID set_publisher_id_;
  jmethodID set_ad_at_point_;
  jmethodID remove_ad_;
  jmethodID prepare_full_screen_ad_;
  jmethodID show_full_screen_ad_;
  jmethodID is_showing_full_screen_ad_;
};

#endif
