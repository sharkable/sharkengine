//
//  ViewController.h
//  AirHockey
//
//  Created by Jonathan Sharkey on 4/1/12.
//  Copyright (c) 2012 Sharkable. All rights reserved.
//

#import <Foundation/Foundation.h>

struct GameSize;
class EngineView;

class GameEngine;

@interface ViewController : UIViewController

@property(nonatomic, readonly) GameEngine *gameEngine;
@property(nonatomic, readonly) UIWindow *window;

- (id)initWithGameSize:(GameSize)gameSize;
- (void)start;
- (void)stop;

@end
