//
//  coordinate_types.h
//  GameEngine
//
//  Created by Jon Sharkey on 2013-01-27.
//  Copyright 2013 Sharkable. All rights reserved.
//

#ifndef GAMEENGINE_COORDINATES_COORDINATETYPES_H_
#define GAMEENGINE_COORDINATES_COORDINATETYPES_H_

#include <cmath>
#include <string>

/***************************************\
 "Game" - coordinates in the game world.
\***************************************/

// Game Size

struct GamePoint;

struct GameSize {
  GameSize() {}
  GameSize(GamePoint const &point);

  GameSize(float width, float height) {
    this->width = width;
    this->height = height;
  }

  float width;
  float height;
};

inline bool operator==(const GameSize &size_1, const GameSize &size_2) {
  return size_1.width == size_2.width && size_1.height == size_2.height;
}

inline GameSize operator+(const GameSize &size_1, const GameSize &size_2) {
  return GameSize(size_1.width + size_2.width, size_1.height + size_2.height);
}

inline GameSize operator-(const GameSize &size_1, const GameSize &size_2) {
  return GameSize(size_1.width - size_2.width, size_1.height - size_2.height);
}

inline GameSize operator-(const GameSize &size) {
  return GameSize(-size.width, -size.height);
}

inline GameSize & operator+=(GameSize &size_1, const GameSize &size_2) {
  size_1.width += size_2.width;
  size_1.height += size_2.height;
  return size_1;
}

inline GameSize & operator-=(GameSize &size_1, const GameSize &size_2) {
  size_1.width -= size_2.width;
  size_1.height -= size_2.height;
  return size_1;
}

inline GameSize operator*(const GameSize &size, float scalar) {
  return GameSize(size.width * scalar, size.height * scalar);
}

inline GameSize operator*(float scalar, const GameSize &size) {
  return GameSize(size.width * scalar, size.height * scalar);
}

inline GameSize operator/(const GameSize &size, float scalar) {
  return GameSize(size.width / scalar, size.height / scalar);
}

inline GameSize & operator*=(GameSize &size, float scalar) {
  size.width *= scalar;
  size.height *= scalar;
  return size;
}

inline GameSize & operator/=(GameSize &size, float scalar) {
  size.width /= scalar;
  size.height /= scalar;
  return size;
}


// Game Point

struct GamePoint {
  GamePoint() {}
  GamePoint(GameSize const &size);

  GamePoint(float x, float y) {
    this->x = x;
    this->y = y;
  }

  float x;
  float y;

  inline GamePoint Normalize() {
    float length = sqrt(x * x + y * y);
    return GamePoint(x / length, y / length);
  }

  inline float Angle() {
    return atan2f(y, x) * 180.f / M_PI;
  }
};

inline bool operator==(const GamePoint &point_1, const GamePoint &point_2) {
  return point_1.x == point_2.x && point_1.y == point_2.y;
}

inline GamePoint operator+(const GamePoint &point_1, const GamePoint &point_2) {
  return GamePoint(point_1.x + point_2.x, point_1.y + point_2.y);
}

inline GamePoint operator-(const GamePoint &point_1, const GamePoint &point_2) {
  return GamePoint(point_1.x - point_2.x, point_1.y - point_2.y);
}

inline GamePoint operator-(const GamePoint &point) {
  return GamePoint(-point.x, -point.y);
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

inline GamePoint operator*(const GamePoint &point, float scalar) {
  return GamePoint(point.x * scalar, point.y * scalar);
}

inline GamePoint operator*(float scalar, const GamePoint &point) {
  return GamePoint(point.x * scalar, point.y * scalar);
}

inline GamePoint operator/(const GamePoint &point, float scalar) {
  return GamePoint(point.x / scalar, point.y / scalar);
}

inline GamePoint & operator*=(GamePoint &point, float scalar) {
  point.x *= scalar;
  point.y *= scalar;
  return point;
}

inline GamePoint & operator/=(GamePoint &point, float scalar) {
  point.x /= scalar;
  point.y /= scalar;
  return point;
}


// GameRect

struct GameRect {
  GameRect(float x, float y, float width, float height) {
    this->origin.x = x;
    this->origin.y = y;
    this->size.width = width;
    this->size.height = height;
  }

  GameRect(GamePoint origin, GameSize size) {
    this->origin = origin;
    this->size = size;
  }

  GamePoint origin;
  GameSize size;

  inline GamePoint TopLeft() { return origin; }
  inline GamePoint TopRight() { return origin + GamePoint(size.width, 0); }
  inline GamePoint BottomLeft() { return origin + GamePoint(0, size.height); }
  inline GamePoint BottomRight() { return origin + GamePoint(size.width, size.height); }
};

inline GamePoint rect_center(GameRect rect) {
  return GamePoint(rect.origin.x + rect.size.width / 2, rect.origin.y + rect.size.height / 2);
}

static const GameSize kGameSizeZero(0, 0);
static const GamePoint kGamePointZero(0, 0);
static const GameRect kGameRectZero(0, 0, 0, 0);


/**************************************\
 "Screen" - coordinates in pixel space.
\**************************************/


// ScreenSize

struct ScreenSize {
  ScreenSize() {}

  ScreenSize(float width, float height) {
    this->width = width;
    this->height = height;
  }

  float width;
  float height;
};


// ScreenPoint

struct ScreenPoint {
  ScreenPoint() {}

  ScreenPoint(float x, float y) {
    this->x = x;
    this->y = y;
  }

  float x;
  float y;
};

inline ScreenPoint operator+(const ScreenPoint &point_1, const ScreenPoint &point_2) {
  return ScreenPoint(point_1.x + point_2.x, point_1.y + point_2.y);
}

inline ScreenPoint operator-(const ScreenPoint &point_1, const ScreenPoint &point_2) {
  return ScreenPoint(point_1.x - point_2.x, point_1.y - point_2.y);
}

inline ScreenPoint operator-(const ScreenPoint &point) {
  return ScreenPoint(-point.x, -point.y);
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

static const ScreenSize kScreenSizeZero(0, 0);
static const ScreenPoint kScreenPointZero(0, 0);


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
