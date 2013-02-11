//
//  view_entity.h
//  AirHockey
//
//  Created by Jonathan Sharkey on 10-04-10.
//  Copyright 2010 Sharkable. All rights reserved.
//

#ifndef AIRHOCKEY_GAMEENGINE_VIEWENTITY_H_
#define AIRHOCKEY_GAMEENGINE_VIEWENTITY_H_

#include <vector>
using namespace std;

class Touch;

class ViewEntity {
 public:
  virtual void Update() = 0;
  virtual void Render() = 0;
  virtual void TouchesBegan(vector<Touch> touches) {}
  virtual void TouchesMoved(vector<Touch> touches) {}
  virtual void TouchesEnded(vector<Touch> touches) {}
  virtual void ClearTouches() {}
};

#endif
