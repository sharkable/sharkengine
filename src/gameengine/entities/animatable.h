//
//  animatable.h
//  GameEngine
//
//  Created by Jon Sharkey on 2/26/13.
//
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

  void AnimateToPosition(GamePoint position, AnimationType animationType, int ticks);
  void AnimateToAngle(double angle, AnimationType animationType, int ticks);

  // VewEntity
  void Update();
  
  // Accessors
  GamePoint position() { return position_; }
  void set_position(GamePoint position) { position_ = position; }
  double angle() { return angle_; }
  void set_angle(double angle) { angle_ = angle; }

 private:
  GamePoint position_;
  double angle_;
  Animation _x_animation;
  Animation _y_animation;
  Animation _angle_animation;
};

#endif
