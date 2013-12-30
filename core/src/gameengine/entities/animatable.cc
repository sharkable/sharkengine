//
//  animatable.cpp
//  GameEngine
//
//  Created by Jon Sharkey on 2013-02-26.
//  Copyright 2013 Sharkable. All rights reserved.
//

#include "gameengine/entities/animatable.h"

Animatable::Animatable()
    : delegate_(nullptr),
      position_(kGamePointZero),
      angle_(0),
      alpha_(1),
      zoom_(1) {
}

Animatable::Animatable(GamePoint position)
    : delegate_(nullptr),
      position_(position),
      angle_(0),
      alpha_(1),
      zoom_(1) {
}

void Animatable::AnimateToPosition(GamePoint position, AnimationType animation_type, int ticks) {
  x_animation_.Reset(position_.x, position.x, ticks, animation_type);
  y_animation_.Reset(position_.y, position.y, ticks, animation_type);
}

void Animatable::AnimateToAngle(double angle, AnimationType animation_type, int ticks) {
  angle_animation_.Reset(angle_, angle, ticks, animation_type);
}

void Animatable::AnimateToAlpha(double alpha, AnimationType animation_type, int ticks) {
  alpha_animation_.Reset(alpha_, alpha, ticks, animation_type);
}

void Animatable::AnimateToZoom(double zoom, AnimationType animation_type, int ticks) {
  zoom_animation_.Reset(zoom_, zoom, ticks, animation_type);
}


#pragma mark - Simulator

void Animatable::SimulateStep() {
  bool call_delegate = false;
  if (x_animation_.IsActive()) {
    position_.x = x_animation_.Update();
    call_delegate = !x_animation_.IsActive();
  }
  if (y_animation_.IsActive()) {
    position_.y = y_animation_.Update();
    call_delegate = !y_animation_.IsActive();
  }
  if (angle_animation_.IsActive()) {
    angle_ = angle_animation_.Update();
    call_delegate = !angle_animation_.IsActive();
  }
  if (alpha_animation_.IsActive()) {
    alpha_ = alpha_animation_.Update();
    call_delegate = !alpha_animation_.IsActive();
  }
  if (zoom_animation_.IsActive()) {
    zoom_ = zoom_animation_.Update();
    call_delegate = !zoom_animation_.IsActive();
  }
  if (delegate_ && call_delegate) {
    delegate_->AnimationFinished(this);
  }
}
