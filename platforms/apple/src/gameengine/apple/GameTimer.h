//
//  GameTimer.h
//  GameEngine
//
//  Created by Jon Sharkey on 2012-02-26.
//  Copyright 2012 Sharkable. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface GameTimer : NSObject

- (id)initWithTarget:(id)target selector:(SEL)selector;

- (void)start;
- (void)stop;

@end
