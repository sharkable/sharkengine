//
//  app_store_engine_android.h
//  GameEngine
//
//  Created by Jon Sharkey on 2013-07-19.
//  Copyright 2013 Sharkable. All rights reserved.
//

#include <jni.h>
#include <string>

#include "gameengine/modules/app_store_engine.h"

#ifndef GAMEENGINE_IOS_APPSTOREENGINEANDROID_H_
#define GAMEENGINE_IOS_APPSTOREENGINEANDROID_H_

class AppStoreEngineAndroid : public AppStoreEngine {
 public:
  AppStoreEngineAndroid(JNIEnv *jni_env, jobject java_object);
   ~AppStoreEngineAndroid();

  // AppStoreEngine
  void AskForRate();
  void AskForUpgrade(std::string app_name, std::string purchase_id,
                     AppStoreEngineDelegate *delegate);

 private:
  JNIEnv *jni_env_;
  jobject java_object_;
  jmethodID ask_for_rate_;
  jmethodID ask_for_upgrade_;
};

#endif
