//
//  coordinate_system.h
//  GameEngine
//
//  Created by Jon Sharkey on 2013-12-10.
//  Copyright 2013 Sharkable. All rights reserved.
//

#ifndef GAMEENGINE_COORDINATES_COORDINATESYSTEM_H_
#define GAMEENGINE_COORDINATES_COORDINATESYSTEM_H_

#include "gameengine/coordinates/coordinate_types.h"

class CoordinateSystem {
 public:
  static CoordinateSystem const & BaseSystem();

  GamePoint ConvertPoint(GamePoint p) const;
  CoordinateSystem Translate(GamePoint translation) const;
  CoordinateSystem Rotate(float angle) const;
  CoordinateSystem Scale(float scale) const;
  CoordinateSystem Subsystem(float angle, GamePoint origin) const {
    shark_assert(false, "deprecated.");
  }

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
