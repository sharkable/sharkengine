//
//  animatable.h
//  SharkEngine
//
//  Created by Jon Sharkey on 2013-02-26.
//  Copyright 2013 Sharkable. All rights reserved.
//

#ifndef SHARKENGINE_ENTITIES_ANIMATABLE_H_
#define SHARKENGINE_ENTITIES_ANIMATABLE_H_

#include "gameengine/animation.h"
#include "gameengine/coordinates/coordinate_types.h"
#include "gameengine/simulation/simulator.h"

class Animatable;

class AnimatableDelegate {
 public:
  virtual void AnimationFinished(Animatable *animatable) = 0;
};

class Animatable : public Simulator {
 public:
  Animatable();
  Animatable(GamePoint position);

  void AnimateToPosition(GamePoint position, AnimationType animation_type, int ticks);
  void AnimateToAngle(double angle, AnimationType animation_type, int ticks);
  void AnimateToAlpha(double alpha, AnimationType animation_type, int ticks);
  void AnimateToScale(double scale, AnimationType animation_type, int ticks);

  // Simulator
  void SimulateStep();

  // Accessors
  AnimatableDelegate *delegate() { return delegate_; }
  void set_animatable_delegate(AnimatableDelegate *delegate) { delegate_ = delegate; }
  GamePoint position() { return position_; }
  void set_position(GamePoint position) { position_ = position; }
  double angle() { return angle_; }
  void set_angle(double angle) { angle_ = angle; }
  double alpha() { return alpha_; }
  void set_alpha(double alpha) { alpha_ = alpha; }
  double scale() { return scale_; }
  void set_scale(double scale) { scale_ = scale; }

 private:
  AnimatableDelegate *delegate_;

  GamePoint position_;
  double angle_;
  double alpha_;
  double scale_;

  Animation x_animation_;
  Animation y_animation_;
  Animation angle_animation_;
  Animation alpha_animation_;
  Animation scale_animation_;
};

#endif
