//
//  AnalyticsEngineAndroid.java
//  GameEngine
//
//  Created by Jon Sharkey on 2013-07-01. (Oh Canada!)
//  Copyright 2013 Sharkable. All rights reserved.
//

package com.sharkable.sharkengine.modules;

import android.util.Log;
import java.util.HashMap;

import com.flurry.android.FlurryAgent;

// TODO I don't think should be all static just because Flurry is.
public class AnalyticsEngineAndroid {
  private static String mEventName = null;
  private static HashMap mParameters = new HashMap();

  public static void beginLogEvent(String eventName) {
    assert(mEventName == null);
    mEventName = eventName;
  }

  public static void addParameter(String key, String value) {
    mParameters.put(key, value);
  }

  public static void commitLogEvent() {
    if (mParameters.size() == 0) {
      FlurryAgent.logEvent(mEventName);
    } else {
      FlurryAgent.logEvent(mEventName, (HashMap)mParameters.clone());
    }
    mEventName = null;
    mParameters.clear();
  }
}
