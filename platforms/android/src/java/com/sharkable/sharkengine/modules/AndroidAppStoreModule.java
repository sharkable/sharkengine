//
//  AppStoreEngineAndroid.java
//  GameEngine
//
//  Created by Jon Sharkey on 2013-07-19.
//  Copyright 2013 Sharkable. All rights reserved.
//

package com.sharkable.sharkengine.modules;

import android.util.Log;

import com.sharkable.sharkengine.SharkengineActivity;

public class AppStoreEngineAndroid {
  private SharkengineActivity mActivity = null;

  public AppStoreEngineAndroid(SharkengineActivity activity) {
    mActivity = activity;
  }

  public void askForRate() {
  }

  public void askForUpgrade(String appName, String purchaseId) {
    Log.d("Sharkable", "APP NAME: " + appName + "  purchaseId: " + purchaseId);
  }
}
