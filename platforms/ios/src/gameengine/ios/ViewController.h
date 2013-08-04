//
//  ViewController.h
//  GameEngine
//
//  Created by Jon Sharkey on 2012-04-01.
//  Copyright 2012 Sharkable. All rights reserved.
//

#import <Foundation/Foundation.h>

struct GameSize;
class EngineView;

class GameEngine;

@interface ViewController : UIViewController

@property(nonatomic, readonly) GameEngine *gameEngine;
@property(nonatomic, readonly) UIWindow *window;

- (void)start;
- (void)stop;
- (BOOL)isLandscape;

@end
