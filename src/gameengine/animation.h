//
//  animation.h
//  AirHockey
//
//  Created by Jon Sharkey on 2/26/13.
//
//

#ifndef GAMEENGINE_ANIMATION_
#define GAMEENGINE_ANIMATION_

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

  void Reset(float start, float distance, int ticks, AnimationType type);
  double Update();
  bool IsActive();

 private:
  float start_;
  float distance_;
  int ticks_;
  int totalTicks_;
  AnimationType type_;
};

#endif

