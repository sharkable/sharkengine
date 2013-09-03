package com.sharkable.sharkengine.modules;

import android.content.Context;
import android.content.SharedPreferences;
import android.util.Log;

public class LocalStoreAndroid {
  private SharedPreferences mPreferences;

  public LocalStoreAndroid(Context context) {
    // TODO use the app name for the name here.
    mPreferences = context.getSharedPreferences("com.sharkable.sharkengine", Context.MODE_PRIVATE);
  }

  public boolean hasEntryForKey(String key) {
    return mPreferences.contains(key);
  }

  public boolean boolForKey(String key) {
    return mPreferences.getBoolean(key, false);
  }

  public void setBool(boolean value, String key) {
    mPreferences.edit().putBoolean(key, value).apply();
  }

  public int integerForKey(String key) {
    return mPreferences.getInt(key, 0);
  }

  public void setInteger(int value, String key) {
    mPreferences.edit().putInt(key, value).apply();
  }

  public double doubleForKey(String key) {
    return mPreferences.getFloat(key, 0.0f);
  }

  public void setDouble(double value, String key) {
    // TODO do I wanna use floats or doubles generally, in this game engine?
    mPreferences.edit().putFloat(key, (float)value).apply();
  }

  public String stringForKey(String key) {
    return mPreferences.getString(key, "");
  }

  void setString(String value, String key) {
    mPreferences.edit().putString(key, value).apply();
  }
}
