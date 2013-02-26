//
//  animatable.h
//  GameEngine
//
//  Created by Jon Sharkey on 2/26/13.
//
//

#ifndef GAMEENGINE_ENTITIES_ANIMATABLE_H_
#define GAMEENGINE_ENTITIES_ANIMATABLE_H_

#include "gameengine/coordinate_types.h"
#include "gameengine/view_entity.h"

class Animatable : public ViewEntity {
 public:
  Animatable();
  Animatable(GamePoint position);

  // Accessors
  GamePoint position() { return position_; }
  void set_position(GamePoint position) { position_ = position; }
  double angle() { return angle_; }
  void set_angle(double angle) { angle_ = angle; }

 private:
  GamePoint position_;
  double angle_;
};

#endif
