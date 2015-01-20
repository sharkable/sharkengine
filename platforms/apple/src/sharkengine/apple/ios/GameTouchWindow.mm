//
//  GameTouchWindow.m
//  SharkEngine
//
//  Created by Jon Sharkey on 2012-02-26.
//  Copyright 2012 Sharkable. All rights reserved.
//

#import "GameTouchWindow.h"

#import "sharkengine/shark_engine.h"

@interface GameTouchWindow ()
- (void)addTouches:(NSSet *)touches action:(InputEvent::Action)action;
@end

@implementation GameTouchWindow {
 @private
  SharkEngine *gameEngine_;  // weak
  CGFloat scale_;
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
  [self addTouches:touches action:InputEvent::kActionDown];
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event {
  [self addTouches:touches action:InputEvent::kActionMove];
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event {
  [self addTouches:touches action:InputEvent::kActionUp];
}

- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event {
  [self addTouches:touches action:InputEvent::kActionCancel];
}


#pragma mark - Private

- (void)addTouches:(NSSet *)touches action:(InputEvent::Action)action {
  for (UITouch *touch : touches) {
    InputManager::PlatformEventId platform_id = (InputManager::PlatformEventId)touch;
    CGPoint window_point = [touch locationInView:touch.view];
    ScreenPoint screen_point(window_point.x * scale_, window_point.y * scale_);
    GamePoint location = gameEngine_->screen_point_to_game_point(screen_point);
    gameEngine_->input_manager().AddTouch(platform_id, action, location);
  }
}

@end
