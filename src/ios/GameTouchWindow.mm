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
  CGFloat scale_;
  double move_factor_;
}

@synthesize gameEngine = gameEngine_;

- (id)initWithFrame:(CGRect)frame {
  self = [super initWithFrame:frame];
  if (self) {
    scale_ = [UIScreen mainScreen].scale;
  }
  return self;
}

#pragma mark - UIWindow

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event {
  move_factor_ = 0;
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

    // Fudge the point by some factor of the velocity, to prevent the lag in movement.
    CGPoint previous_location = [touch previousLocationInView:touch.view];
    double diff_x = location.x - previous_location.x;
    double diff_y = location.y - previous_location.y;
    double new_factor = 0;
    double velocity_squared = diff_x * diff_x + diff_y * diff_y;
    if (velocity_squared > 25 * 25) {
      new_factor = 1.5;
    } else {
      new_factor = velocity_squared / (25 * 25 / 1.5);
    }
    move_factor_ = (move_factor_ + new_factor) / 2;
    location.x = location.x + diff_x * move_factor_;
    location.y = location.y + diff_y * move_factor_;

    ScreenPoint l = screen_point_make(location.x * scale_, location.y * scale_);
    GamePoint p = gameEngine_->screen_point_to_game_point(l);
    converted_touch.set_location(p);
    converted_touch.set_identifier(touch);
    converted_touches.push_back(converted_touch);
  }
  return converted_touches;
}

@end
