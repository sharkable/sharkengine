//
//  coordinate_system.cc
//  GameEngine
//
//  Created by Jon Sharkey on 2013-12-10.
//  Copyright 2013 Sharkable. All rights reserved.
//

// See Sharkable Notes vol. 1 page 25.

#include <cmath>

#include "gameengine/coordinates/coordinate_system.h"

CoordinateSystem const & CoordinateSystem::BaseSystem() {
  return base_system_;
}


GamePoint CoordinateSystem::ConvertPoint(GamePoint p) const {
  if (angle_ == 0.f) {
    return p + origin_;
  }
  return GamePoint(cos_angle_ * p.x - sin_angle_ * p.y + origin_.x,
                   sin_angle_ * p.x + cos_angle_ * p.y + origin_.y);
}

CoordinateSystem CoordinateSystem::Subsystem(float angle, GamePoint origin) const {
  CoordinateSystem subsystem;
  subsystem.angle_ = angle_ + angle;
  subsystem.origin_ = ConvertPoint(origin);
  if (angle == 0.f) {
    subsystem.cos_angle_ = cos_angle_;
    subsystem.sin_angle_ = sin_angle_;
  } else {
    subsystem.cos_angle_ = cosf(subsystem.angle_ * M_PI / 180.f);
    subsystem.sin_angle_ = sinf(subsystem.angle_ * M_PI / 180.f);
  }
  return subsystem;
}


#pragma mark - private

CoordinateSystem CoordinateSystem::base_system_;

// Constructs the system used for BaseSystem().
CoordinateSystem::CoordinateSystem()
    : angle_(0.f),
      origin_(kGamePointZero),
      cos_angle_(1.f),
      sin_angle_(0.f) {
}
