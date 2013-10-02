//
//  touch.h
//  GameEngine
//
//  Created by Jon Sharkey on 2010-04-30.
//  Copyright 2010 Sharkable. All rights reserved.
//

#ifndef GAMEENGINE_TOUCH_H_
#define GAMEENGINE_TOUCH_H_

#include <sstream>
#include <string>

#include "gameengine/coordinate_types.h"

class Touch {
 public:
  GamePoint location() const { return location_; }
  void set_location(GamePoint location) { location_ = location; }
  void *identifier() const { return identifier_; }
  void set_identifier(void *identifier) { identifier_ = identifier; }

  // debug
  std::string ToString() {
    std::ostringstream out_string;
    out_string << "Touch " << identifier() << "\t" << location().x << ", " << location().y;
    return out_string.str();
  }

 private:
  GamePoint location_;
  void *identifier_;
};

#endif
