//
//  GameTimer.h
//  AirHockey
//
//  Created by Jonathan Sharkey on 2/26/12.
//  Copyright (c) 2012 Sharkable. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface GameTimer : NSObject

- (id)initWithTarget:(id)target selector:(SEL)selector;

- (void)start;
- (void)stop;

@end
