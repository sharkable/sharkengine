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
  Positions(string filename);
  GamePoint position(string name) { return positions_[name]; }

 private:
  map<string, GamePoint> positions_;
  void LoadFile(string filename);
};

#endif
