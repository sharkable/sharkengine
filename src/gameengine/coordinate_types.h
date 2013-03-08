//
//  coordinate_types.h
//  GameEngine
//
//  Created by Jon Sharkey on 2013-01-27.
//  Copyright 2013 Sharkable. All rights reserved.
//

#ifndef GAMEENGINE_COORDINATETYPES_H
#define GAMEENGINE_COORDINATETYPES_H

// "Game" - coordinates in the game world.

struct GameSize {
  double width;
  double height;
};

inline GameSize game_size_make(double width, double height) {
  GameSize size;
  size.width = width;
  size.height = height;
  return size;
}

struct GamePoint {
  double x;
  double y;
};

inline GamePoint game_point_make(double x, double y) {
  GamePoint point;
  point.x = x;
  point.y = y;
  return point;
}

static const GamePoint kGamePointZero = game_point_make(0, 0);


// "Screen" - coordinates in pixel space.

struct ScreenSize {
  double width;
  double height;
};

inline ScreenSize screen_size_make(double width, double height) {
  ScreenSize size;
  size.width = width;
  size.height = height;
  return size;
}

struct ScreenPoint {
  double x;
  double y;
};

inline ScreenPoint screen_point_make(double x, double y) {
  ScreenPoint point;
  point.x = x;
  point.y = y;
  return point;
}

static const ScreenPoint kScreenPointZero = screen_point_make(0, 0);

#endif
