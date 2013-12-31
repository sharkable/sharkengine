//
//  GameTouchWindow.m
//  GameEngine
//
//  Created by Jon Sharkey on 2012-02-26.
//  Copyright 2012 Sharkable. All rights reserved.
//

#import "GameTouchWindow.h"

#include <vector>
using std::vector;

#import "gameengine/game_engine.h"

@interface GameTouchWindow ()
- (std::vector<InputEvent>)convertTouches:(NSSet *)touches action:(InputEvent::Action)action;
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
  vector<InputEvent> converted_touches =
      [self convertTouches:touches action:InputEvent::kActionDown];
  for (InputEvent event : converted_touches) {
    gameEngine_->AddInputEvent(event);
  }
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event {
  vector<InputEvent> converted_touches =
      [self convertTouches:touches action:InputEvent::kActionMove];
  for (InputEvent event : converted_touches) {
    gameEngine_->AddInputEvent(event);
  }
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event {
  vector<InputEvent> converted_touches =
      [self convertTouches:touches action:InputEvent::kActionUp];
  for (InputEvent event : converted_touches) {
    gameEngine_->AddInputEvent(event);
  }
}

#pragma mark - Private

- (vector<InputEvent>)convertTouches:(NSSet *)touches action:(InputEvent::Action)action {
  vector<InputEvent> converted_touches;
  for (UITouch *touch in touches) {
    CGPoint location = [touch locationInView:touch.view];

// TODO: Should this be a game option? I was using it in Air Hockey.
// TODO: Compare new threading method input to this and to old method. Maybe the new
//     threading method is enough to fix this.
#if 0
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
#endif

    ScreenPoint l(location.x * scale_, location.y * scale_);
    GamePoint p = gameEngine_->screen_point_to_game_point(l);
    InputEvent converted_touch(action, InputEvent::kIdTouch0, p);
    converted_touches.push_back(converted_touch);
  }
  return converted_touches;
}

@end
