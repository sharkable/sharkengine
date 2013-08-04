//
//  ViewController.m
//  GameEngine
//
//  Created by Jon Sharkey on 2012-04-01.
//  Copyright 2012 Sharkable. All rights reserved.
//

#import "gameengine/ios/ViewController.h"

#import "gameengine/ios/AdEngineIOS.h"
#import "gameengine/ios/AnalyticsEngineIOS.h"
#import "gameengine/ios/AppStoreEngineIOS.h"
#import "gameengine/ios/EAGLView.h"
#import "gameengine/ios/GameTimer.h"
#import "gameengine/ios/GameTouchWindow.h"
#import "gameengine/ios/LocalStoreIOS.h"
#import "gameengine/opengl/texture2d.h"
#import "gameengine/game_engine.h"

@interface ViewController ()
- (void)update;
- (BOOL)isLandscape;
@end

@implementation ViewController {
 @private
  EAGLView *view_;
  GameTimer *gameTimer_;
  GameTouchWindow *gameTouchWindow_;

  GameEngine *gameEngine_;
};

@synthesize window = gameTouchWindow_, gameEngine = gameEngine_;

- (id)init {
  self = [super init];
  if (self) {
    CGRect screenSize = [[UIScreen mainScreen] bounds];
    gameTouchWindow_ = [[GameTouchWindow alloc] initWithFrame:screenSize];
    [gameTouchWindow_ setRootViewController:self];
    [gameTouchWindow_ makeKeyAndVisible];

    gameEngine_ = new GameEngine();

    PlatformType platform_type = (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPhone) ?
        kPlatformTypePhone : kPlatformTypeTablet;
    PlatformResolution platform_resolution = [UIScreen mainScreen].scale == 2 ?
        kPlatformResolutionHigh : kPlatformResolutionLow;
    gameEngine_->set_platform_type(platform_type);
    gameEngine_->set_platform_resolution(platform_resolution);

    gameEngine_->set_local_store(sp<LocalStore>(new LocalStoreIOS()));
    gameEngine_->set_ad_engine(sp<AdEngine>(new AdEngineIOS(self)));
    gameEngine_->set_analytics_engine(sp<AnalyticsEngine>(new AnalyticsEngineIOS()));
    gameEngine_->set_app_store_engine(sp<AppStoreEngine>(new AppStoreEngineIOS()));

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

// For iOS 5

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
  if ([self isLandscape]) {
    return (interfaceOrientation == UIInterfaceOrientationLandscapeLeft ||
            interfaceOrientation == UIInterfaceOrientationLandscapeRight);
  }
  return (interfaceOrientation == UIInterfaceOrientationPortrait ||
          interfaceOrientation == UIInterfaceOrientationPortraitUpsideDown);
}

// For iOS 6

- (BOOL)shouldAutorotate {
  return YES;
}

- (NSUInteger)supportedInterfaceOrientations {
  if ([self isLandscape]) {
    return UIInterfaceOrientationMaskLandscape;
  }
  return UIInterfaceOrientationMaskPortrait | UIInterfaceOrientationMaskPortraitUpsideDown;
}


#pragma mark - Private

- (void)update {
  gameEngine_->Update();
  [view_ setUpRender];
  gameEngine_->Render();
  [view_ finishRender];
}

- (BOOL)isLandscape {
  NSArray *supportedOrientations =
      [[NSBundle mainBundle] objectForInfoDictionaryKey:@"UISupportedInterfaceOrientations"];
  for (NSString *orientation in supportedOrientations) {
    if ([orientation isEqualToString:@"UIInterfaceOrientationLandscapeLeft"] ||
        [orientation isEqualToString:@"UIInterfaceOrientationLandscapeRight"]) {
      return YES;
    }
  }
  return NO;
}

@end
