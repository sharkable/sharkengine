//
//  AdEngineIOS.h
//  AirHockey
//
//  Created by Jon Sharkey on 2/7/13.
//
//

#ifndef GAMEENGINE_IOS_ADENGINEIOS_H_
#define GAMEENGINE_IOS_ADENGINEIOS_H_

#import "gameengine/ad_engine.h"

@class GADBannerView;

class AdEngineIOS : public AdEngine {
 public:
  AdEngineIOS(UIViewController *root_view_controller);
  ~AdEngineIOS();

  // AdEngine
  void SetAdAtPoint(ScreenPoint point);
  void RemoveAd();

 private:
  GADBannerView *banner_view_;
  UIViewController *root_view_controller_;
};

#endif
