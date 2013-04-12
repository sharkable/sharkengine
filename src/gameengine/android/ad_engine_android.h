//
//  AdEngineAndroid.h
//  GameEngine
//
//  Created by Jon Sharkey on 2013-04-09.
//  Copyright 2013 Sharkable. All rights reserved.
//

#ifndef GAMEENGINE_IOS_ADENGINEANDROID_H_
#define GAMEENGINE_IOS_ADENGINEANDROID_H_

#include "gameengine/ad_engine.h"

class AdEngineAndroid : public AdEngine {
 public:
  // AdEngine
  void SetAdAtPoint(ScreenPoint point);
  void RemoveAd();
  bool ShowFullScreenAd();
  bool IsShowingFullScreenAd();
};

#endif
