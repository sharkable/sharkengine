//
//  ViewController.h
//  SharkEngine
//
//  Created by Jon Sharkey on 2012-04-01.
//  Copyright 2012 Sharkable. All rights reserved.
//

#import <Foundation/Foundation.h>

struct GameSize;
class EngineView;

class SharkEngine;

@interface ViewController : UIViewController

@property(nonatomic, readonly) SharkEngine *gameEngine;
@property(nonatomic, readonly) UIWindow *window;

- (void)pause;
- (void)start;

@end
