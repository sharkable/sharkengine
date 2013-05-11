//
//  AdEngineIOS.h
//  GameEngine
//
//  Created by Jon Sharkey on 2013-02-07.
//  Copyright 2013 Sharkable. All rights reserved.
//

#ifndef GAMEENGINE_IOS_ADENGINEIOS_H_
#define GAMEENGINE_IOS_ADENGINEIOS_H_

#include <string>

#include "gameengine/modules/ad_engine.h"

@class GADBannerView;
@class GADInterstitial;
@class InterstitialState;

class AdEngineIOS : public AdEngine {
 public:
  AdEngineIOS(UIViewController *root_view_controller);
  ~AdEngineIOS();

  // AdEngine
  void SetPublisherId(std::string publisher_id);
  void SetAdAtPoint(ScreenPoint point);
  void RemoveAd();
  void PrepareFullScreenAd();
  bool ShowFullScreenAd();
  bool IsShowingFullScreenAd();

 private:
  std::string publisher_id_;
  GADBannerView *banner_view_;
  GADInterstitial *interstitial_;
  InterstitialState *interstitial_state_;
  UIViewController *root_view_controller_;
};

#endif
