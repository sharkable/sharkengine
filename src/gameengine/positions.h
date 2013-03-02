//
//  positions.h
//  GameEngine
//
//  Created by Jon Sharkey on 2/19/13.
//
//

#ifndef GAMEENGINE_POSITIONS_H_
#define GAMEENGINE_POSITIONS_H_

#include "gameengine/coordinate_types.h"

#include <map>
using namespace std;

class Positions {
 public:
  GamePoint position(string name) { return positions_[name]; }
  void LoadFile(string filename);

 private:
  map<string, GamePoint> positions_;
};

#endif
