//
//  ad_engine.h
//  AirHockey
//
//  Created by Jonathan Sharkey on 2/25/12.
//  Copyright (c) 2012 Sharkable. All rights reserved.
//

#ifndef GAMEENGINE_ADENGINE_H_
#define GAMEENGINE_ADENGINE_H_

struct ScreenPoint;

class AdEngine {
 public:
  virtual void SetAdAtPoint(ScreenPoint point) = 0;
  virtual void RemoveAd() = 0;
};

#endif
