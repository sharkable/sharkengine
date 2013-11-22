//
//  animation.cc
//  GameEngine
//
//  Created by Jon Sharkey on 2013-02-26.
//  Copyright 2013 Sharkable. All rights reserved.
//

#include "gameengine/animation.h"

#include "thirdparty/PennerEasing/Bounce.h"
#include "thirdparty/PennerEasing/Cubic.h"
#include "thirdparty/PennerEasing/Linear.h"

Animation::Animation()
    : start_(0),
      distance_(0),
      ticks_(0),
      total_ticks_(0),
      type_(kAnimationTypeLinear) {
}

void Animation::Reset(float start, float end, int ticks, AnimationType type) {
  start_ = start;
  end_ = end;
  distance_ = end - start;
  ticks_ = 0;
  total_ticks_ = ticks;
  type_ = type;
}

double Animation::Update() {
  ticks_++;
  if (ticks_ >= total_ticks_) {
    return end_;
  }
  switch (type_) {
    case kAnimationTypeLinear:
      return Linear::easeNone(ticks_, start_, distance_, total_ticks_);
    case kAnimationTypeCubicEaseIn:
      return Cubic::easeIn(ticks_, start_, distance_, total_ticks_);
    case kAnimationTypeCubicEaseOut:
      return Cubic::easeOut(ticks_, start_, distance_, total_ticks_);
    case kAnimationTypeCubicEaseInOut:
      return Cubic::easeInOut(ticks_, start_, distance_, total_ticks_);
    case kAnimationTypeBounceEaseIn:
      return Bounce::easeIn(ticks_, start_, distance_, total_ticks_);
    case kAnimationTypeBounceEaseOut:
      return Bounce::easeOut(ticks_, start_, distance_, total_ticks_);
    case kAnimationTypeBounceEaseInOut:
      return Bounce::easeInOut(ticks_, start_, distance_, total_ticks_);
  }
}

bool Animation::IsActive() {
  return ticks_ < total_ticks_;
}

void Animation::Stop() {
  ticks_ = 0;
  total_ticks_ = 0;
}
