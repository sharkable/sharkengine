//
//  AdEngineAndroid.java
//  GameEngine
//
//  Created by Jon Sharkey on 2013-06-30.
//  Copyright 2013 Sharkable. All rights reserved.
//

package com.sharkable.sharkengine.modules;

import android.util.Log;
import java.util.HashSet;

import com.google.ads.AdListener;
import com.google.ads.Ad;
import com.google.ads.AdRequest;
import com.google.ads.AdSize;
import com.google.ads.AdView;
import com.google.ads.InterstitialAd;

import com.sharkable.sharkengine.SharkengineActivity;

public class AdEngineAndroid {
  private class InterstitialState implements AdListener {
    private boolean mIsShowing = false;

    public boolean isShowing() {
      return mIsShowing;
    }


    // AdListener

    public void onDismissScreen(Ad ad) {
      mIsShowing = false;
    }
    
    public void onFailedToReceiveAd(Ad ad, AdRequest.ErrorCode error) {
    }
    
    public void onLeaveApplication(Ad ad) {
    }
    
    public void onPresentScreen(Ad ad) {
      mIsShowing = true;
    }
    
    public void onReceiveAd(Ad ad) {
    }
  }

  private SharkengineActivity mActivity = null;
  private AdView mBannerView = null;
  private InterstitialAd mInterstitial = null;
  private InterstitialState mInterstitialState = new InterstitialState();
  private String mPublisherId = null;

  public AdEngineAndroid(SharkengineActivity activity) {
    mActivity = activity;
  }

  public void setPublisherId(String publisherId) {
    mPublisherId = publisherId;
  }

  public void setAdAtPoint(float point /* TODO get a valid coodinate here. */) {
    mActivity.runOnUiThread(new Runnable() {           
      @Override
      public void run() {
        if (mBannerView == null) {
          assert(mPublisherId != null);
          mBannerView = new AdView(mActivity, AdSize.IAB_BANNER, mPublisherId);

          AdRequest request = new AdRequest();
          HashSet testDevices = new HashSet();
          testDevices.add(AdRequest.TEST_EMULATOR);
          request.setTestDevices(testDevices);
          mBannerView.loadAd(request);
        }
        // TODO ad to view hierarchy.
      }
    });
  }

  public void removeAd() {
    mActivity.runOnUiThread(new Runnable() {           
      @Override
      public void run() {
       // TODO remove from view hierarchy.
       mBannerView.destroy();
       mBannerView = null;
      }
    });
  }

  public void prepareFullScreenAd() {
    mActivity.runOnUiThread(new Runnable() {           
      @Override
      public void run() {
        assert(mPublisherId != null);
        mInterstitial = new InterstitialAd(mActivity, mPublisherId);
        mInterstitial.setAdListener(mInterstitialState);

        AdRequest request = new AdRequest();
        HashSet testDevices = new HashSet();
        testDevices.add(AdRequest.TEST_EMULATOR);
        request.setTestDevices(testDevices);
        mInterstitial.loadAd(request);
      }
    });
  }

  public boolean showFullScreenAd() {
    if (mInterstitial != null && mInterstitial.isReady()) {
      mActivity.runOnUiThread(new Runnable() {           
        @Override
        public void run() {
          // TODO this is kinda hacky. Avoid causing a pause notification for the ad.
          mActivity.ignoreNextPause();
          mInterstitial.show();
          prepareFullScreenAd();
        }
      });
      return true;
    }
    return false;
  }

  public boolean isShowingFullScreenAd() {
    return mInterstitialState.isShowing();
  }
}
