//
//  positions.h
//  GameEngine
//
//  Created by Jon Sharkey on 2013-02-19.
//  Copyright 2013 Sharkable. All rights reserved.
//

#ifndef GAMEENGINE_POSITIONS_H_
#define GAMEENGINE_POSITIONS_H_

#include "gameengine/coordinate_types.h"

#include <map>

class Positions {
 public:
  GamePoint position(std::string name) { return positions_[name]; }
  void LoadFile(std::string filename);

 private:
  std::map<std::string, GamePoint> positions_;
};

#endif
