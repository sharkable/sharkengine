//
//  animatable.cpp
//  GameEngine
//
//  Created by Jon Sharkey on 2/26/13.
//
//

#include "gameengine/entities/animatable.h"

Animatable::Animatable()
    : position_(kGamePointZero),
      angle_(0) {
}

Animatable::Animatable(GamePoint position)
    : position_(position),
      angle_(0) {
}

void Animatable::AnimateToPosition(GamePoint position, AnimationType animationType, int ticks) {
  _x_animation.Reset(position_.x, position.x - position_.x, ticks, animationType);
  _y_animation.Reset(position_.y, position.x - position_.y, ticks, animationType);
}

void Animatable::AnimateToAngle(double angle, AnimationType animationType, int ticks) {
  _angle_animation.Reset(angle_, angle - angle_, ticks, animationType);
}


// ViewEntity

void Animatable::Update() {
  if (_x_animation.IsActive()) {
    position_.x = _x_animation.Update();
  }
  if (_y_animation.IsActive()) {
    position_.y = _y_animation.Update();
  }
  if (_angle_animation.IsActive()) {
    angle_ = _angle_animation.Update();
  }
}
