//
//  GameTouchWindow.h
//  GameEngine
//
//  Created by Jon Sharkey on 2012-02-26.
//  Copyright 2012 Sharkable. All rights reserved.
//

#import <Foundation/Foundation.h>

class GameEngine;

@interface GameTouchWindow : UIWindow

@property(nonatomic, assign) GameEngine *gameEngine;

@end
