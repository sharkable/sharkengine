//
//  coordinate_types.h
//  GameEngine
//
//  Created by Jon Sharkey on 2013-01-27.
//  Copyright 2013 Sharkable. All rights reserved.
//

#ifndef GAMEENGINE_COORDINATETYPES_H_
#define GAMEENGINE_COORDINATETYPES_H_

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

inline GamePoint operator+(const GamePoint &point_1, const GamePoint &point_2) {
  return game_point_make(point_1.x + point_2.x, point_1.y + point_2.y);
}

inline GamePoint operator-(const GamePoint &point_1, const GamePoint &point_2) {
  return game_point_make(point_1.x - point_2.x, point_1.y - point_2.y);
}

struct GameRect {
  GamePoint origin;
  GameSize size;
};

inline GameRect game_rect_make(double x, double y, double width, double height) {
  GameRect rect;
  rect.origin.x = x;
  rect.origin.y = y;
  rect.size.width = width;
  rect.size.height = height;
  return rect;
}

inline GameRect game_rect_make(GamePoint origin, GameSize size) {
  GameRect rect;
  rect.origin = origin;
  rect.size = size;
  return rect;
}

static const GameSize kGameSizeZero = game_size_make(0, 0);
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

static const ScreenSize kScreenSizeZero = screen_size_make(0, 0);
static const ScreenPoint kScreenPointZero = screen_point_make(0, 0);

#endif
