//
//  android_persistence_module.cc
//  SharkEngine
//
//  Created by Jon Sharkey on 2013-05-15.
//  Copyright 2013 Sharkable. All rights reserved.
//

#include "sharkengine/android/modules/android_persistence_module.h"

using std::string;

AndroidPersistenceModule::AndroidPersistenceModule(JNIEnv *jni_env, jobject java_object)
    : jni_env_(jni_env) {
  java_object_ = jni_env->NewGlobalRef(java_object);
  jclass java_class =
      jni_env_->FindClass("com/sharkable/sharkengine/modules/AndroidPersistenceModule");
  has_entry_for_key_ = jni_env_->GetMethodID(java_class, "hasEntryForKey", "(Ljava/lang/String;)Z");
  bool_for_key_ = jni_env_->GetMethodID(java_class, "boolForKey", "(Ljava/lang/String;)Z");
  set_bool_ = jni_env_->GetMethodID(java_class, "setBool", "(ZLjava/lang/String;)V");
  integer_for_key_ = jni_env_->GetMethodID(java_class, "integerForKey", "(Ljava/lang/String;)I");
  set_integer_ = jni_env_->GetMethodID(java_class, "setInteger", "(ILjava/lang/String;)V");
  double_for_key_ = jni_env_->GetMethodID(java_class, "doubleForKey", "(Ljava/lang/String;)D");
  set_double_ = jni_env_->GetMethodID(java_class, "setDouble", "(DLjava/lang/String;)V");
  string_for_key_ =
      jni_env_->GetMethodID(java_class, "stringForKey", "(Ljava/lang/String;)Ljava/lang/String;");
  set_string_ =
      jni_env_->GetMethodID(java_class, "setString", "(Ljava/lang/String;Ljava/lang/String;)V");
}

AndroidPersistenceModule::~AndroidPersistenceModule() {
  jni_env_->DeleteGlobalRef(java_object_);
}


// PersistenceModule

bool AndroidPersistenceModule::HasEntryForKey(string key) {
  jstring java_key = jni_env_->NewStringUTF(key.c_str());
  bool value = jni_env_->CallBooleanMethod(java_object_, has_entry_for_key_, java_key);
  jni_env_->DeleteLocalRef(java_key);
  return value;
}

bool AndroidPersistenceModule::BoolForKey(string key) {
  jstring java_key = jni_env_->NewStringUTF(key.c_str());
  bool value = jni_env_->CallBooleanMethod(java_object_, bool_for_key_, java_key);
  jni_env_->DeleteLocalRef(java_key);
  return value;
}

void AndroidPersistenceModule::SetBool(bool value, string key) {
  jstring java_key = jni_env_->NewStringUTF(key.c_str());
  jni_env_->CallVoidMethod(java_object_, set_bool_, value, java_key);
  jni_env_->DeleteLocalRef(java_key);
}

int AndroidPersistenceModule::IntegerForKey(string key) {
  jstring java_key = jni_env_->NewStringUTF(key.c_str());
  int value = jni_env_->CallIntMethod(java_object_, integer_for_key_, java_key);
  jni_env_->DeleteLocalRef(java_key);
  return value;
}

void AndroidPersistenceModule::SetInteger(int value, string key) {
  jstring java_key = jni_env_->NewStringUTF(key.c_str());
  jni_env_->CallVoidMethod(java_object_, set_integer_, value, java_key);
  jni_env_->DeleteLocalRef(java_key);
}

double AndroidPersistenceModule::DoubleForKey(string key) {
  jstring java_key = jni_env_->NewStringUTF(key.c_str());
  double value = jni_env_->CallDoubleMethod(java_object_, double_for_key_, java_key);
  jni_env_->DeleteLocalRef(java_key);
  return value;
}

void AndroidPersistenceModule::SetDouble(double value, string key) {
  jstring java_key = jni_env_->NewStringUTF(key.c_str());
  jni_env_->CallVoidMethod(java_object_, set_double_, value, java_key);
  jni_env_->DeleteLocalRef(java_key);
}

string AndroidPersistenceModule::StringForKey(string key) {
  // TODO this is not tested at all, and I'm not sure about the memory allocations.
  assert(false); // FAIL on this. If I start using it, test it.

  jstring java_key = jni_env_->NewStringUTF(key.c_str());
  jstring value = (jstring)jni_env_->CallObjectMethod(java_object_, string_for_key_, java_key);
  jboolean is_copy;
  const char *c_str = jni_env_->GetStringUTFChars(value, &is_copy);
  string cpp_string(c_str);
  jni_env_->ReleaseStringUTFChars(value, c_str);
  jni_env_->DeleteLocalRef(java_key);
  jni_env_->DeleteLocalRef(value);
  return cpp_string;
}

void AndroidPersistenceModule::SetString(string value, string key) {
  jstring java_value = jni_env_->NewStringUTF(value.c_str());
  jstring java_key = jni_env_->NewStringUTF(key.c_str());
  jni_env_->CallVoidMethod(java_object_, set_string_, java_value, java_key);
  jni_env_->DeleteLocalRef(java_value);
  jni_env_->DeleteLocalRef(java_key);
}
