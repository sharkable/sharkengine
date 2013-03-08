//
//  GameTimer.m
//  GameEngine
//
//  Created by Jon Sharkey on 2012-02-26.
//  Copyright 2012 Sharkable. All rights reserved.
//

#import <QuartzCore/QuartzCore.h>

#import "GameTimer.h"

@implementation GameTimer {
 @private
  id target_;  // weak
  SEL selector_;
  
  BOOL animating_;
  BOOL displayLinkSupported_;
  // Use of the CADisplayLink class is the preferred method for controlling your animation timing.
  // CADisplayLink will link to the main display and fire every vsync when added to a given
  // run-loop. The NSTimer class is used only as fallback when running on a pre 3.1 device where
  // CADisplayLink isn't available.
  id displayLink_;
  NSTimer *animationTimer_;
}

- (id)initWithTarget:(id)target selector:(SEL)selector {
  self = [super init];
  if (self) {
    target_ = target;
    selector_ = selector;
    
    // A system version of 3.1 or greater is required to use CADisplayLink. The NSTimer
    // class is used as fallback when it isn't available.
    NSString *reqSysVer = @"3.1";
    NSString *currSysVer = [[UIDevice currentDevice] systemVersion];
    if ([currSysVer compare:reqSysVer options:NSNumericSearch] != NSOrderedAscending) {
      displayLinkSupported_ = YES;
    }
  }
  return self;
}

- (void)dealloc {
  [displayLink_ release];
  [animationTimer_ release];
  
  [super dealloc];
}

- (void)start {
  if (!animating_) {
    // Do one tick immediately, then rely on the timer for subsequent ticks.
    [target_ performSelector:selector_];
    if (displayLinkSupported_) {
      // CADisplayLink is API new to iPhone SDK 3.1. Compiling against earlier versions will result
      // in a warning, but can be dismissed if the system version runtime check for CADisplayLink
      // exists in -initWithCoder:. The runtime check ensures this code will not be called in system
      // versions earlier than 3.1.
      
      displayLink_ =
          [[NSClassFromString(@"CADisplayLink") displayLinkWithTarget:target_
                                                             selector:selector_] retain];
      [displayLink_ setFrameInterval:1];  // 60 fps
      [displayLink_ addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
    } else {
      NSTimeInterval interval = (NSTimeInterval)(1.0 / 60.0);
      animationTimer_ = [[NSTimer scheduledTimerWithTimeInterval:interval
                                                          target:target_
                                                        selector:selector_
                                                        userInfo:nil
                                                         repeats:YES] retain];
    }
    
    animating_ = YES;
  }
}

- (void)stop {
  if (animating_) {
    if (displayLinkSupported_) {
      [displayLink_ invalidate];
      [displayLink_ release];
      displayLink_ = nil;
    } else {
      [animationTimer_ invalidate];
      [animationTimer_ release];
      animationTimer_ = nil;
    }
    
    animating_ = NO;
  }
}

@end
