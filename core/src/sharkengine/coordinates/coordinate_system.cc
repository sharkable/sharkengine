//
//  coordinate_system.cc
//  SharkEngine
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


#pragma mark - System Transformations

CoordinateSystem CoordinateSystem::Translate(GamePoint translation) const {
  CoordinateSystem subsystem(*this);
  subsystem.origin_ = PointToBasePoint(translation);
  return subsystem;
}

CoordinateSystem CoordinateSystem::Rotate(float angle) const {
  CoordinateSystem subsystem(*this);
  if (angle != 0.f) {
    subsystem.angle_ += angle;
    subsystem.cos_angle_ = cosf(subsystem.angle_ * M_PI / 180.f);
    subsystem.sin_angle_ = sinf(subsystem.angle_ * M_PI / 180.f);
  }
  return subsystem;
}

CoordinateSystem CoordinateSystem::Scale(float scale) const {
  CoordinateSystem subsystem(*this);
  subsystem.scale_ *= scale;
  return subsystem;
}

CoordinateSystem CoordinateSystem::ScaleAroundPoint(float scale, GamePoint point) const {
  CoordinateSystem subsystem = Translate(point * (1 - scale));
  subsystem.scale_ *= scale;
  return subsystem;
}


#pragma mark - Convert to and from BaseSystem

GamePoint CoordinateSystem::PointToBasePoint(GamePoint p) const {
  if (angle_ == 0.f) {
    return p * scale_ + origin_;
  }
  return GamePoint((cos_angle_ * p.x - sin_angle_ * p.y) * scale_ + origin_.x,
                   (sin_angle_ * p.x + cos_angle_ * p.y) * scale_ + origin_.y);
}

GamePoint CoordinateSystem::BasePointToPoint(GamePoint p) const {
  GamePoint point = (p - origin_) * (1.f / scale_);
  if (angle_ == 0.f) {
    return point;
  }
  return GamePoint(cos_angle_ * point.x + sin_angle_ * point.y,
                   -sin_angle_ * point.x + cos_angle_ * point.y);
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
