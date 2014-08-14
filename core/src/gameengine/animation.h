//
//  animation.h
//  SharkEngine
//
//  Created by Jon Sharkey on 2013-02-26.
//  Copyright 2013 Sharkable. All rights reserved.
//

#ifndef GAMEENGINE_ANIMATION_H_
#define GAMEENGINE_ANIMATION_H_

typedef enum {
  kAnimationTypeLinear = 0,
  kAnimationTypeCubicEaseIn,
  kAnimationTypeCubicEaseOut,
  kAnimationTypeCubicEaseInOut,
  kAnimationTypeBounceEaseIn,
  kAnimationTypeBounceEaseOut,
  kAnimationTypeBounceEaseInOut
} AnimationType;

class Animation {
 public:
  Animation();

  void Reset(float start, float end, int ticks, AnimationType type);
  double Value();
  double Update();
  bool IsActive();
  void Stop();

 private:
  float start_;
  float end_;
  float distance_;
  int ticks_;
  int total_ticks_;
  AnimationType type_;
};

#endif
