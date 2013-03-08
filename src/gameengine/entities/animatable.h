//
//  animatable.h
//  GameEngine
//
//  Created by Jon Sharkey on 2013-02-26.
//  Copyright 2013 Sharkable. All rights reserved.
//

#ifndef GAMEENGINE_ENTITIES_ANIMATABLE_H_
#define GAMEENGINE_ENTITIES_ANIMATABLE_H_

#include "gameengine/animation.h"
#include "gameengine/coordinate_types.h"
#include "gameengine/view_entity.h"

class Animatable : public ViewEntity {
 public:
  Animatable();
  Animatable(GamePoint position);

  void AnimateToPosition(GamePoint position, AnimationType animation_type, int ticks);
  void AnimateToAngle(double angle, AnimationType animation_type, int ticks);
  void AnimateToAlpha(double alpha, AnimationType animation_type, int ticks);
  void AnimateToZoom(double zoom, AnimationType animation_type, int ticks);

  // VewEntity
  void Update();
  
  // Accessors
  GamePoint position() { return position_; }
  void set_position(GamePoint position) { position_ = position; }
  double angle() { return angle_; }
  void set_angle(double angle) { angle_ = angle; }
  double alpha() { return alpha_; }
  void set_alpha(double alpha) { alpha_ = alpha; }
  double zoom() { return zoom_; }
  void set_zoom(double zoom) { zoom_ = zoom; }

 private:
  GamePoint position_;
  double angle_;
  double alpha_;
  double zoom_;

  Animation _x_animation;
  Animation _y_animation;
  Animation _angle_animation;
  Animation _alpha_animation;
  Animation _zoom_animation;
};

#endif
