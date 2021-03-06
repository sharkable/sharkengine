//
//  ViewController.m
//  SharkEngine
//
//  Created by Jon Sharkey on 2012-04-01.
//  Copyright 2012 Sharkable. All rights reserved.
//

#import "sharkengine/apple/ios/ViewController.h"

#import "sharksound/apple/AppleSoundController.h"

#import "sharkengine/apple/ios/EAGLView.h"
#import "sharkengine/apple/ios/GameTouchWindow.h"
#import "sharkengine/apple/modules/ApplePersistenceModule.h"
#import "sharkengine/apple/modules/ios/IOSAdModule.h"
#import "sharkengine/apple/modules/ios/IOSAnalyticsModule.h"
#import "sharkengine/apple/modules/ios/IOSAppStoreModule.h"
#import "sharkengine/apple/modules/ios/IOSAssetReaderFactoryModule.h"
#import "sharkengine/apple/modules/ios/IOSIAdAdModule.h"
#import "sharkengine/apple/modules/ios/IOSInputModule.h"
#import "sharkengine/opengl/texture2d.h"
#import "sharkengine/shark_engine.h"
#import "sharkengine/platform.h"

@interface ViewController ()
- (void)setup;
- (void)runGameLoop;
- (BOOL)isLandscape;
- (CGRect)desiredViewFrame;
@end

@implementation ViewController {
 @private
  EAGLView *view_;
  GameTouchWindow *gameTouchWindow_;

  SharkEngine *gameEngine_;
  BOOL paused_;
  BOOL renderedAtLeastOnce_;
};

@synthesize window = gameTouchWindow_, gameEngine = gameEngine_;

- (id)init {
  self = [super init];
  if (self) {
    gameTouchWindow_ = [[GameTouchWindow alloc] initWithFrame:[UIScreen mainScreen].bounds];
    [gameTouchWindow_ setRootViewController:self];
    [gameTouchWindow_ makeKeyAndVisible];
  }
  return self;
}

- (void)dealloc {
  delete gameEngine_;

  [view_ release];
  [gameTouchWindow_ release];

  [super dealloc];
}

- (void)pause {
  paused_ = YES;
}

- (void)start {
  paused_ = NO;
}


#pragma mark - UIViewController

- (void)loadView {
  // TODO: Consider handling viewDidUnload: to free memory.
  if (!view_) {
    view_ = [[EAGLView alloc] initWithFrame:[self desiredViewFrame]];
    [self setup];
    while (!renderedAtLeastOnce_) {
      // TODO This is needed, or this is an infinite loop in release mode. Investigate.
      [NSThread sleepForTimeInterval:0.1];
    }
  }
  self.view = view_;
}

- (void)viewWillDisappear:(BOOL)animated {
  [self pause];
}

-  (void)viewDidAppear:(BOOL)animated {
  [self start];
}

// For iOS 5

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
#if SP_APP_DISABLE_ORIENTATION_FLIP
  if ([self isLandscape]) {
    return (interfaceOrientation == UIInterfaceOrientationLandscapeLeft);
  }
  return (interfaceOrientation == UIInterfaceOrientationPortrait);
#else
  if ([self isLandscape]) {
    return (interfaceOrientation == UIInterfaceOrientationLandscapeLeft ||
            interfaceOrientation == UIInterfaceOrientationLandscapeRight);
  }
  return (interfaceOrientation == UIInterfaceOrientationPortrait ||
          interfaceOrientation == UIInterfaceOrientationPortraitUpsideDown);
#endif
}

// For iOS 6

- (BOOL)shouldAutorotate {
  return YES;
}

- (NSUInteger)supportedInterfaceOrientations {
#if SP_APP_DISABLE_ORIENTATION_FLIP
  if ([self isLandscape]) {
    return UIInterfaceOrientationMaskLandscapeLeft;
  }
  return UIInterfaceOrientationMaskPortrait;
#else
  if ([self isLandscape]) {
    return UIInterfaceOrientationMaskLandscape;
  }
  return UIInterfaceOrientationMaskPortrait | UIInterfaceOrientationMaskPortraitUpsideDown;
#endif
}


#pragma mark - Private

- (void)setup {
  gameEngine_ = new SharkEngine();

  CGSize screenSize = [self desiredViewFrame].size;
  CGFloat scale = [UIScreen mainScreen].scale;
  gameEngine_->set_screen_size(ScreenSize(screenSize.width * scale,                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      screenSize.height * scale));

  bool is_phone = UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPhone;
  bool is_high_res = [UIScreen mainScreen].scale == 2;
  bool is_4_inch = [UIScreen mainScreen].bounds.size.height > 480;

  Platform::ScreenSizeGroup screen_size_group;
  Platform::TextureGroup texture_group;
  if (is_phone) {
    screen_size_group = Platform::kScreenSizeGroupPhone;
    if (is_high_res) {
      if (is_4_inch) {
        texture_group = Platform::kTextureGroupIPhone40cmHighRes;
      } else {
        texture_group = Platform::kTextureGroupIPhone35cmHighRes;
      }
    } else {
      texture_group = Platform::kTextureGroupIPhone35cmLowRes;
    }
  } else {
    screen_size_group = Platform::kScreenSizeGroupTablet;
    if (is_high_res) {
      texture_group = Platform::kTextureGroupIPadHighRes;
    } else {
      texture_group = Platform::kTextureGroupIPadLowRes;
    }
  }

  gameEngine_->platform().set_screen_size_group(screen_size_group);
  gameEngine_->platform().set_os_group(Platform::kOSGroupIOS);
  gameEngine_->platform().set_input_group(Platform::kInputGroupTouchScreen);
  gameEngine_->platform().set_texture_group(texture_group);

  gameEngine_->set_asset_reader_factory_module(
      sp<AssetReaderFactoryModule>(new IOSAssetReaderFactoryModule()));
  gameEngine_->set_persistence_module(sp<PersistenceModule>(new ApplePersistenceModule()));
  // Use iAd on iPad, and AdMob on iPhone. iAd only supports full screen ads on iPad.
  if (screen_size_group == Platform::kScreenSizeGroupPhone) {
    gameEngine_->set_ad_module(sp<AdModule>(new IOSAdModule(self)));
  } else {
    gameEngine_->set_ad_module(sp<AdModule>(new IOSIAdAdModule(self)));
  }
  gameEngine_->set_analytics_module(sp<AnalyticsModule>(new IOSAnalyticsModule()));
  gameEngine_->set_app_store_module(sp<AppStoreModule>(new IOSAppStoreModule()));
  gameEngine_->set_input_module(sp<InputModule>(new IOSInputModule()));
  gameEngine_->set_sound(sp<SharkSound::SoundController>(new SharkSound::AppleSoundController()));

  gameTouchWindow_.gameEngine = gameEngine_;

  [NSThread detachNewThreadSelector:@selector(runGameLoop) toTarget:self withObject:nil];
}

- (void)runGameLoop {
  [view_ initRenderer];
  sharkengine_init(*gameEngine_);

  double last_system_time = CACurrentMediaTime();
  double accumulator = 0;
  static const double kTimeDelta = 1.0 / 60.0;

  [[NSThread currentThread] setThreadPriority:1.0];
  while (true) {
    if (paused_) {
// TODO NOW      gameEngine_->NotifyPause();
      while (paused_) {
        // TODO This is needed, or this is an infinite loop in release mode. Investigate.
        [NSThread sleepForTimeInterval:0.1];
      }
      last_system_time = CACurrentMediaTime();
    }

    double current_system_time = CACurrentMediaTime();
    double time_diff = current_system_time - last_system_time;
    last_system_time = current_system_time;
    accumulator += time_diff;

    while (accumulator >= 2 * kTimeDelta) {
      gameEngine_->Update();
      accumulator -= kTimeDelta;
    }

    gameEngine_->Update();
    accumulator -= kTimeDelta;

    [view_ setUpRender];
    gameEngine_->Render();
    [view_ finishRender];

    renderedAtLeastOnce_ = YES;
  }
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

@end
