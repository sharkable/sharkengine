//
//  android_app_store_module.cc
//  SharkEngine
//
//  Created by Jon Sharkey on 2013-07-219.
//  Copyright 2013 Sharkable. All rights reserved.
//

#include "sharkengine/android/modules/android_app_store_module.h"

AndroidAppStoreModule::AndroidAppStoreModule(JNIEnv *jni_env, jobject java_object)
    : jni_env_(jni_env) {
  java_object_ = jni_env->NewGlobalRef(java_object);
  jclass java_class =
      jni_env_->FindClass("com/sharkable/sharkengine/modules/AndroidAppStoreModule");
  ask_for_rate_ = jni_env_->GetMethodID(java_class, "askForRate", "()V");
  ask_for_upgrade_ =
      jni_env_->GetMethodID(java_class, "askForUpgrade", "(Ljava/lang/String;Ljava/lang/String;)V");
}

AndroidAppStoreModule::~AndroidAppStoreModule() {
  jni_env_->DeleteGlobalRef(java_object_);
}


// AppStoreModule

void AndroidAppStoreModule::AskForRate() {
  jni_env_->CallVoidMethod(java_object_, ask_for_rate_);
}

void AndroidAppStoreModule::AskForUpgrade(std::string app_name, std::string purchase_id,
                                          AppStoreModuleDelegate *delegate) {
  jstring java_app_name = jni_env_->NewStringUTF(app_name.c_str());
  jstring java_purchase_id = jni_env_->NewStringUTF(purchase_id.c_str());
  jni_env_->CallVoidMethod(java_object_, ask_for_upgrade_, java_app_name, java_purchase_id);
  jni_env_->DeleteLocalRef(java_app_name);
  jni_env_->DeleteLocalRef(java_purchase_id);
}
