//
//  animatable.cpp
//  GameEngine
//
//  Created by Jon Sharkey on 2/26/13.
//
//

#include "gameengine/entities/animatable.h"

Animatable::Animatable()
    : position_(kGamePointZero),
      angle_(0) {
}

Animatable::Animatable(GamePoint position)
    : position_(position),
      angle_(0) {
}
