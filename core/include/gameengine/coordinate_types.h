//
//  coordinate_types.h
//  GameEngine
//
//  Created by Jon Sharkey on 2013-01-27.
//  Copyright 2013 Sharkable. All rights reserved.
//

#ifndef GAMEENGINE_COORDINATETYPES_H_
#define GAMEENGINE_COORDINATETYPES_H_

#include <string>

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

inline GamePoint & operator+=(GamePoint &point_1, const GamePoint &point_2) {
  point_1.x += point_2.x;
  point_1.y += point_2.y;
  return point_1;
}

inline GamePoint & operator-=(GamePoint &point_1, const GamePoint &point_2) {
  point_1.x -= point_2.x;
  point_1.y -= point_2.y;
  return point_1;
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

inline GamePoint rect_center(GameRect rect) {
  return game_point_make(rect.origin.x + rect.size.width / 2, rect.origin.y + rect.size.height / 2);
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

inline ScreenPoint operator+(const ScreenPoint &point_1, const ScreenPoint &point_2) {
  return screen_point_make(point_1.x + point_2.x, point_1.y + point_2.y);
}

inline ScreenPoint operator-(const ScreenPoint &point_1, const ScreenPoint &point_2) {
  return screen_point_make(point_1.x - point_2.x, point_1.y - point_2.y);
}

inline ScreenPoint & operator+=(ScreenPoint &point_1, const ScreenPoint &point_2) {
  point_1.x += point_2.x;
  point_1.y += point_2.y;
  return point_1;
}

inline ScreenPoint & operator-=(ScreenPoint &point_1, const ScreenPoint &point_2) {
  point_1.x -= point_2.x;
  point_1.y -= point_2.y;
  return point_1;
}

static const ScreenSize kScreenSizeZero = screen_size_make(0, 0);
static const ScreenPoint kScreenPointZero = screen_point_make(0, 0);



#pragma mark - debug

static const int kBufferSize = 1024;

inline std::string to_string(GameSize size) {
  char buffer[kBufferSize];
  sprintf(buffer, "{%f, %f}", size.width, size.height);
  return std::string(buffer);
}

inline std::string to_string(GamePoint point) {
  char buffer[kBufferSize];
  sprintf(buffer, "{%f, %f}", point.x, point.y);
  return std::string(buffer);
}

inline std::string to_string(GameRect rect) {
  char buffer[kBufferSize];
  sprintf(buffer, "{{%g, %g}, {%g, %g}}", rect.origin.x, rect.origin.y, rect.size.width,
          rect.size.height);
  return std::string(buffer);
}

inline std::string to_string(ScreenSize size) {
  char buffer[kBufferSize];
  sprintf(buffer, "{%f, %f}", size.width, size.height);
  return std::string(buffer);
}

inline std::string to_string(ScreenPoint point) {
  char buffer[kBufferSize];
  sprintf(buffer, "{%f, %f}", point.x, point.y);
  return std::string(buffer);
}

#endif
