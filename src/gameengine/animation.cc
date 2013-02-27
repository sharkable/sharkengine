//
//  animation.cc
//  AirHockey
//
//  Created by Jon Sharkey on 2/26/13.
//
//

#include "gameengine/animation.h"

#include "thirdparty/PennerEasing/Bounce.h"
#include "thirdparty/PennerEasing/Cubic.h"
#include "thirdparty/PennerEasing/Linear.h"

Animation::Animation()
    : start_(0),
      distance_(0),
      ticks_(0),
      totalTicks_(0),
      type_(kAnimationTypeLinear) {
}

void Animation::Reset(float start, float distance, int ticks, AnimationType type) {
  start_ = start;
  distance_ = distance;
  ticks_ = 0;
  totalTicks_ = ticks;
  type_ = type;
}

double Animation::Update() {
  ticks_++;
  switch (type_) {
    case kAnimationTypeLinear:
      return Linear::easeNone(ticks_, start_, distance_, totalTicks_);
    case kAnimationTypeCubicEaseIn:
      return Cubic::easeIn(ticks_, start_, distance_, totalTicks_);
    case kAnimationTypeCubicEaseOut:
      return Cubic::easeOut(ticks_, start_, distance_, totalTicks_);
    case kAnimationTypeCubicEaseInOut:
      return Cubic::easeInOut(ticks_, start_, distance_, totalTicks_);
    case kAnimationTypeBounceEaseIn:
      return Bounce::easeIn(ticks_, start_, distance_, totalTicks_);
    case kAnimationTypeBounceEaseOut:
      return Bounce::easeOut(ticks_, start_, distance_, totalTicks_);
    case kAnimationTypeBounceEaseInOut:
      return Bounce::easeInOut(ticks_, start_, distance_, totalTicks_);
  }
}

bool Animation::IsActive() {
  return ticks_ < totalTicks_;
}
