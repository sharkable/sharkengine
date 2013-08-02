//
//  SharkengineOpenGLView.h
//  Air Hockey
//
//  Created by Jon Sharkey on 2013-07-29.
//  Copyright (c) 2013 Jon Sharkey. All rights reserved.
//

#import <Foundation/Foundation.h>

#include "game_engine.h"

@interface SharkengineOpenGLView : NSOpenGLView

- (void)drawRect:(NSRect)bounds;
+ (void)setGameEngine:(GameEngine *)gameEngine;

@end
