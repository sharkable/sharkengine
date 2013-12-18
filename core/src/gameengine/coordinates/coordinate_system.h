//
//  coordinate_system.h
//  Pigeon
//
//  Created by Jon Sharkey on 2013-12-10.
//  Copyright 2013 Sharkable. All rights reserved.
//

#ifndef PIGEON_UPDATERS_COORDINATESYSTEM_H_
#define PIGEON_UPDATERS_COORDINATESYSTEM_H_

#include "gameengine/coordinates/coordinate_types.h"

class CoordinateSystem {
 public:
  static CoordinateSystem const & BaseSystem();

  GamePoint ConvertPoint(GamePoint p) const;
  CoordinateSystem Subsystem(float angle, GamePoint origin) const;

  float angle() const { return angle_; }
  GamePoint origin() const { return origin_; }

 private:
  float angle_;
  GamePoint origin_;
  float cos_angle_;
  float sin_angle_;
  static CoordinateSystem base_system_;

  CoordinateSystem();
};

#endif
