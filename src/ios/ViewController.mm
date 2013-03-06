//
//  ViewController.m
//  AirHockey
//
//  Created by Jonathan Sharkey on 4/1/12.
//  Copyright (c) 2012 Sharkable. All rights reserved.
//

#import "ios/ViewController.h"

#import "ios/AdEngineIOS.h"
#import "ios/AnalyticsEngineIOS.h"
#import "ios/EAGLView.h"
#import "ios/GameTimer.h"
#import "ios/GameTouchWindow.h"
#import "gameengine/game_engine.h"
#import "opengl/texture2d.h"

@implementation ViewController {
 @private
  EAGLView *view_;
  GameTimer *gameTimer_;
  GameTouchWindow *gameTouchWindow_;

  GameEngine *gameEngine_;
};

@synthesize window = gameTouchWindow_, gameEngine = gameEngine_;

- (id)initWithGameSize:(GameSize)gameSize {
  self = [super init];
  if (self) {
    CGRect screenSize = [[UIScreen mainScreen] bounds];
    gameTouchWindow_ = [[GameTouchWindow alloc] initWithFrame:screenSize];
    [gameTouchWindow_ addSubview:self.view];
    [gameTouchWindow_ makeKeyAndVisible];

    gameEngine_ = new GameEngine();
    PlatformType platform_type = (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPhone) ?
        kPlatformTypePhone : kPlatformTypeTablet;
    gameEngine_->set_platform_type(platform_type);
    gameEngine_->set_ad_engine(sp<AdEngine>(new AdEngineIOS(self)));
    gameEngine_->set_analytics_engine(sp<AnalyticsEngine>(new AnalyticsEngineIOS()));

    CGSize size = [UIScreen mainScreen].bounds.size;
    CGFloat scale = [UIScreen mainScreen].scale;
    gameEngine_->SetScreenSize(screen_size_make(size.width * scale, size.height * scale),
                               gameSize);

    gameTimer_ = [[GameTimer alloc] initWithTarget:self selector:@selector(update)];
    gameTouchWindow_.gameEngine = gameEngine_;    
  }
  return self;
}

- (void)dealloc {
  delete gameEngine_;

  [view_ release];
  [gameTimer_ release];
  [gameTouchWindow_ release];

  [super dealloc];
}

- (void)start {
  [gameTimer_ start];
}

- (void)stop {  
  [gameTimer_ stop];
}

#pragma mark - UIViewController

- (void)loadView {
  // TODO: Consider handling viewDidUnload: to free memory.
  if (!view_) {
    view_ = [[EAGLView alloc] initWithFrame:gameTouchWindow_.frame];
  }
  self.view = view_;
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
  return (interfaceOrientation == UIInterfaceOrientationPortrait ||
          interfaceOrientation == UIInterfaceOrientationPortraitUpsideDown);
}

#pragma mark - Private

- (void)update {
  gameEngine_->Update();
  [view_ setUpRender];
  gameEngine_->Render();
  [view_ finishRender];
}

@end
