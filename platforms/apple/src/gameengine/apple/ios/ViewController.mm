//
//  ViewController.m
//  GameEngine
//
//  Created by Jon Sharkey on 2012-04-01.
//  Copyright 2012 Sharkable. All rights reserved.
//

#import "gameengine/apple/ios/ViewController.h"

#import "gameengine/apple/ios/EAGLView.h"
#import "gameengine/apple/ios/GameTimer.h"
#import "gameengine/apple/ios/GameTouchWindow.h"
#import "gameengine/apple/modules/AppleLocalStore.h"
#import "gameengine/apple/modules/ios/IOSAdModule.h"
#import "gameengine/apple/modules/ios/IOSAnalyticsEngine.h"
#import "gameengine/apple/modules/ios/IOSAppStoreEngine.h"
#import "gameengine/apple/modules/ios/IOSIAdAdModule.h"
#import "gameengine/apple/modules/ios/IOSModuleFactory.h"
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
    gameTouchWindow_ = [[GameTouchWindow alloc] initWithFrame:[UIScreen mainScreen].bounds];
    [gameTouchWindow_ setRootViewController:self];
    [gameTouchWindow_ makeKeyAndVisible];

    gameEngine_ = new GameEngine(sp<ModuleFactory>(new IOSModuleFactory()));

    PlatformType platform_type = (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPhone) ?
        kPlatformTypePhone : kPlatformTypeTablet;
    PlatformResolution platform_resolution = [UIScreen mainScreen].scale == 2 ?
        kPlatformResolutionHigh : kPlatformResolutionLow;
    gameEngine_->set_platform_type(platform_type);
    gameEngine_->set_platform_resolution(platform_resolution);

    gameEngine_->set_local_store(sp<LocalStore>(new AppleLocalStore()));
    // Use iAd on iPad, and AdMob on iPhone. iAd only supports full screen ads on iPad.
    if (gameEngine_->platform_type() == kPlatformTypePhone) {
      gameEngine_->set_ad_module(sp<AdModule>(new IOSAdModule(self)));
    } else {
      gameEngine_->set_ad_module(sp<AdModule>(new IOSIAdAdModule(self)));
    }
    gameEngine_->set_analytics_engine(sp<AnalyticsEngine>(new IOSAnalyticsEngine()));
    gameEngine_->set_app_store_engine(sp<AppStoreEngine>(new IOSAppStoreEngine()));

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

- (CGRect)desiredViewFrame {
  CGRect screenFrame = [UIScreen mainScreen].bounds;
  // UIScreen is always in portrait mode. Swap width and height if needed.
  if ([self isLandscape] && screenFrame.size.width < screenFrame.size.height) {
    CGFloat newWidth = screenFrame.size.height;
    screenFrame.size.height = screenFrame.size.width;
    screenFrame.size.width = newWidth;
  }
  return screenFrame;
}


#pragma mark - UIViewController

- (void)loadView {
  // TODO: Consider handling viewDidUnload: to free memory.
  if (!view_) {
    view_ = [[EAGLView alloc] initWithFrame:[self desiredViewFrame]];
  }
  self.view = view_;
}

- (void)viewWillDisappear:(BOOL)animated {
  [self stop];
}

-  (void)viewDidAppear:(BOOL)animated {
  [self start];
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
