package com.sharkable.sharkengine.modules;

import android.util.Log;

public class LocalStoreAndroid {
  public boolean hasEntryForKey(String key) {
    Log.d("Sharkable", "hasEntryForKey: " + key);
    return false;
  }

  public boolean boolForKey(String key) {
    Log.d("Sharkable", "boolForKey: " + key);
    return false;
  }

  public void setBool(boolean value, String key) {
    Log.d("Sharkable", "setBool: " + value + ", " + key);
  }

  public int integerForKey(String key) {
    Log.d("Sharkable", "integerForKey: " + key);
    return 0;
  }

  public void setInteger(int value, String key) {
    Log.d("Sharkable", "setInteger: " + value + ", " + key);
  }

  public double doubleForKey(String key) {
    Log.d("Sharkable", "doubleForKey: " + key);
    return 0;
  }

  public void setDouble(double value, String key) {
    Log.d("Sharkable", "setDouble: " + value + ", " + key);
  }

  public String stringForKey(String key) {
    Log.d("Sharkable", "stringForKey: " + key);
    return "";
  }

  void setString(String value, String key) {
    Log.d("Sharkable", "setString: " + value + ", " + key);
  }
}
