//
//  GameTouchWindow.m
//  AirHockey
//
//  Created by Jonathan Sharkey on 2/26/12.
//  Copyright (c) 2012 Sharkable. All rights reserved.
//

#import "GameTouchWindow.h"

#include <vector>
using namespace std;

#import "game_engine.h"
#import "Touch.h"

@interface GameTouchWindow ()
- (vector<Touch>)convertTouches:(NSSet *)touches;
@end

@implementation GameTouchWindow {
 @private
  GameEngine *gameEngine_;  // weak
}

@synthesize gameEngine = gameEngine_;

#pragma mark - UIWindow

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event {
  gameEngine_->set_touches_began([self convertTouches:touches]);
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event {
  gameEngine_->set_touches_moved([self convertTouches:touches]);
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event {
  gameEngine_->set_touches_ended([self convertTouches:touches]);
}

#pragma mark - Private

- (vector<Touch>)convertTouches:(NSSet *)touches {
  vector<Touch> converted_touches;
  for (UITouch *touch in touches) {
    Touch converted_touch;
    CGPoint location = [touch locationInView:touch.view];
    ScreenPoint l = screen_point_make(location.x, location.y);
    GamePoint p = gameEngine_->screen_point_to_game_point(l);
    converted_touch.set_location(p);
    converted_touch.set_identifier(touch);
    converted_touches.push_back(converted_touch);
  }
  return converted_touches;
}

@end
