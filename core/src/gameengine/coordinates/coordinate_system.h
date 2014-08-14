//
//  coordinate_system.h
//  SharkEngine
//
//  Created by Jon Sharkey on 2013-12-10.
//  Copyright 2013 Sharkable. All rights reserved.
//

#ifndef SHARKENGINE_COORDINATES_COORDINATESYSTEM_H_
#define SHARKENGINE_COORDINATES_COORDINATESYSTEM_H_

#include "gameengine/coordinates/coordinate_types.h"

class CoordinateSystem {
 public:
  static CoordinateSystem const & BaseSystem();

  // System Transformations
  CoordinateSystem Translate(GamePoint translation) const;
  CoordinateSystem Rotate(float angle) const;
  CoordinateSystem Scale(float scale) const;
  CoordinateSystem ScaleAroundPoint(float scale, GamePoint point) const;

  // Convert to and from BaseSystem
  GamePoint PointToBasePoint(GamePoint p) const;
  GamePoint BasePointToPoint(GamePoint p) const;

  // Accessors
  GamePoint origin() const { return origin_; }
  float angle() const { return angle_; }
  float scale() const { return scale_; }

 private:
  GamePoint origin_;
  float angle_;
  float scale_;

  float cos_angle_;
  float sin_angle_;

  static CoordinateSystem base_system_;

  CoordinateSystem();
};

#endif
