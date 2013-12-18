//
//  SharkengineOpenGLView.h
//  Air Hockey
//
//  Created by Jon Sharkey on 2013-07-29.
//  Copyright (c) 2013 Jon Sharkey. All rights reserved.
//

class GameEngine;

#include "gameengine/coordinates/coordinate_types.h"

@interface SharkengineOpenGLView : NSOpenGLView<NSWindowDelegate> {
  BOOL didStart_;
  GameEngine *gameEngine_;
  int viewportX_;
  int viewportY_;
  int viewportWidth_;
  int viewportHeight_;
  ScreenSize renderSize_;
  NSSize windowSize_;
  CGFloat screenScale_;
}

@end
