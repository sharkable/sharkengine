//
//  ViewController.h
//  AirHockey
//
//  Created by Jonathan Sharkey on 4/1/12.
//  Copyright (c) 2012 Sharkable. All rights reserved.
//

#import <Foundation/Foundation.h>

class GameEngine;

@interface ViewController : UIViewController

@property(nonatomic, readonly) GameEngine *game_engine;
@property(nonatomic, readonly) UIWindow *window;

- (void)start;
- (void)stop;

@end
