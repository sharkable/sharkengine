//
//  android_app_store_module.h
//  SharkEngine
//
//  Created by Jon Sharkey on 2013-07-19.
//  Copyright 2013 Sharkable. All rights reserved.
//

#include <jni.h>
#include <string>

#include "gameengine/modules/app_store_module.h"

#ifndef SHARKENGINE_ANDROID_MODULES_ANDROIDAPPSTOREMODULE_H_
#define SHARKENGINE_ANDROID_MODULES_ANDROIDAPPSTOREMODULE_H_

class AndroidAppStoreModule : public AppStoreModule {
 public:
  AndroidAppStoreModule(JNIEnv *jni_env, jobject java_object);
   ~AndroidAppStoreModule();

  // AppStoreModule
  void AskForRate();
  void AskForUpgrade(std::string app_name, std::string purchase_id,
                     AppStoreModuleDelegate *delegate);

  // Module
  bool IsImplemented() { return true; };

 private:
  JNIEnv *jni_env_;
  jobject java_object_;
  jmethodID ask_for_rate_;
  jmethodID ask_for_upgrade_;
};

#endif
