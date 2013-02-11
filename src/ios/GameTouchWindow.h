//
//  GameTouchWindow.h
//  AirHockey
//
//  Created by Jonathan Sharkey on 2/26/12.
//  Copyright (c) 2012 Sharkable. All rights reserved.
//

#import <Foundation/Foundation.h>

class GameEngine;

@interface GameTouchWindow : UIWindow

@property(nonatomic, assign) GameEngine *gameEngine;

@end
