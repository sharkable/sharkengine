//
//  coordinate_types.cc
//  AirHockey_osx
//
//  Created by Jon Sharkey on 2014-07-03.
//  Copyright 2013 Sharkable. All rights reserved.
//

#include "sharkengine/coordinates/coordinate_types.h"

#pragma mark - GameSize

GameSize::GameSize(GamePoint const &point) : width(point.x), height(point.y) {}


#pragma mark - GamePoint

GamePoint::GamePoint(GameSize const &size) : x(size.width), y(size.height) {}