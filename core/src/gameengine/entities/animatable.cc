//
//  animatable.cpp
//  GameEngine
//
//  Created by Jon Sharkey on 2013-02-26.
//  Copyright 2013 Sharkable. All rights reserved.
//

#include "gameengine/entities/animatable.h"

Animatable::Animatable()
    : position_(kGamePointZero),
      angle_(0),
      alpha_(1),
      zoom_(1) {
}

Animatable::Animatable(GamePoint position)
    : position_(position),
      angle_(0),
      alpha_(1),
      zoom_(1) {
}

void Animatable::AnimateToPosition(GamePoint position, AnimationType animation_type, int ticks) {
  _x_animation.Reset(position_.x, position.x - position_.x, ticks, animation_type);
  _y_animation.Reset(position_.y, position.y - position_.y, ticks, animation_type);
}

void Animatable::AnimateToAngle(double angle, AnimationType animation_type, int ticks) {
  _angle_animation.Reset(angle_, angle - angle_, ticks, animation_type);
}

void Animatable::AnimateToAlpha(double alpha, AnimationType animation_type, int ticks) {
  _alpha_animation.Reset(alpha_, alpha - alpha_, ticks, animation_type);
}

void Animatable::AnimateToZoom(double zoom, AnimationType animation_type, int ticks) {
  _zoom_animation.Reset(zoom_, zoom - zoom_, ticks, animation_type);
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
  if (_alpha_animation.IsActive()) {
    alpha_ = _alpha_animation.Update();
  }
  if (_zoom_animation.IsActive()) {
    zoom_ = _zoom_animation.Update();
  }
}
