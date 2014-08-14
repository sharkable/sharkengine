//
//  IOSIAdAdModule.h
//  SharkEngine
//
//  Created by Jon Sharkey on 2013-08-13.
//  Copyright 2013 Sharkable. All rights reserved.
//

#ifndef SHARKENGINE_APPLE_MODULES_IOS_IOSIADADMODULE_H
#define SHARKENGINE_APPLE_MODULES_IOS_IOSIADADMODULE_H

#include <string>

#include "sharkengine/apple/modules/ios/IOSAdModule.h"
#include "sharkengine/modules/ad_module.h"

@class IAdInterstitialState;

class IOSIAdAdModule : public AdModule {
 public:
  IOSIAdAdModule(UIViewController *root_view_controller);
  ~IOSIAdAdModule();

  // AdModule
  void SetPublisherId(const std::string & publisher_id);
  void SetAdAtPoint(ScreenPoint point);
  void RemoveAd();
  void PrepareFullScreenAd();
  bool ShowFullScreenAd();
  bool IsShowingFullScreenAd();

  // Module
  bool IsImplemented() { return true; };

 private:
  IAdInterstitialState *interstitial_state_;
  UIViewController *root_view_controller_;
  // Back up to AdMob if iAd doesn't work.
  IOSAdModule admob_module_;
};

#endif
