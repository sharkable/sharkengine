//
//  ad_engine.h
//  GameEngine
//
//  Created by Jon Sharkey on 2012-02-25.
//  Copyright 2012 Sharkable. All rights reserved.
//

#ifndef GAMEENGINE_ADENGINE_H_
#define GAMEENGINE_ADENGINE_H_

#include <string>

struct ScreenPoint;

class AdEngine {
 public:
  virtual void SetPublisherId(std::string publisher_id) = 0;
  virtual void SetAdAtPoint(ScreenPoint point) = 0;
  virtual void RemoveAd() = 0;
  virtual bool ShowFullScreenAd() = 0;
  virtual bool IsShowingFullScreenAd() = 0;
};

#endif
