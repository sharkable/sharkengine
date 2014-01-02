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
    return p * scale_ + origin_;
  }
  return GamePoint((cos_angle_ * p.x - sin_angle_ * p.y) * scale_ + origin_.x,
                   (sin_angle_ * p.x + cos_angle_ * p.y) * scale_ + origin_.y);
}

CoordinateSystem CoordinateSystem::Translate(GamePoint translation) const {
  CoordinateSystem subsystem;
  subsystem.origin_ = ConvertPoint(translation);
  subsystem.angle_ = angle_;
  subsystem.scale_ = scale_;
  subsystem.cos_angle_ = cos_angle_;
  subsystem.sin_angle_ = sin_angle_;
  return subsystem;
}

CoordinateSystem CoordinateSystem::Rotate(float angle) const {
  CoordinateSystem subsystem;
  subsystem.origin_ = origin_;
  subsystem.angle_ = angle_ + angle;
  subsystem.scale_ = scale_;
  if (angle == 0.f) {
    subsystem.cos_angle_ = cos_angle_;
    subsystem.sin_angle_ = sin_angle_;
  } else {
    subsystem.cos_angle_ = cosf(subsystem.angle_ * M_PI / 180.f);
    subsystem.sin_angle_ = sinf(subsystem.angle_ * M_PI / 180.f);
  }
  return subsystem;
}

CoordinateSystem CoordinateSystem::Scale(float scale) const {
  CoordinateSystem subsystem;
  subsystem.origin_ = origin_;
  subsystem.angle_ = angle_;
  subsystem.scale_ = scale_ * scale;
  subsystem.cos_angle_ = cos_angle_;
  subsystem.sin_angle_ = sin_angle_;
  return subsystem;
}


#pragma mark - private

CoordinateSystem CoordinateSystem::base_system_;

// Constructs the system used for BaseSystem().
CoordinateSystem::CoordinateSystem()
    : origin_(kGamePointZero),
      angle_(0.f),
      scale_(1.f),
      cos_angle_(1.f),
      sin_angle_(0.f) {
}
