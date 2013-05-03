//
//  AppDelegate.m
//  GameEngine
//
//  Created by Jon Sharkey on 2010-05-07.
//  Copyright 2010 Sharkable. All rights reserved.
//

#import "gameengine/ios/AppDelegate.h"

#import "gameengine/ios/thirdparty/flurry/Flurry.h"
#import "gameengine/ios/GameEngineFactoryIOS.h"
#import "gameengine/ios/TypeUtil.h"
#import "gameengine/ios/ViewController.h"
#import "gameengine/modules/sound_player.h"
#import "gameengine/game_engine.h"

@implementation AppDelegate {
 @private
  ViewController *viewController_;
}

- (void)dealloc {
  [viewController_ release];

  [super dealloc];
}

#pragma mark - UIApplicationDelegate

- (BOOL)application:(UIApplication *)application
    didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
  NSString *appVersion = [[[NSBundle mainBundle] infoDictionary] objectForKey:@"CFBundleVersion"];
  [Flurry setAppVersion:appVersion];
  [Flurry startSession:@"BGGPH5B2THWFSJHXEKRH"];

  viewController_ = [[ViewController alloc] init];
  viewController_.gameEngine->set_factory(sp<GameEngineFactory>(new GameEngineFactoryIOS()));

  CGSize screenSize = [UIScreen mainScreen].bounds.size;
  CGFloat scale = [UIScreen mainScreen].scale;
  viewController_.gameEngine->SetScreenSize(screen_size_make(screenSize.width * scale,
                                                             screenSize.height * scale));

  // TODO why is this a shared_ptr?
  sharkengine_init(sp<GameEngine>(viewController_.gameEngine));

  return YES;
}

- (void)applicationWillResignActive:(UIApplication *)application {
  [viewController_ stop];
}

- (void)applicationDidBecomeActive:(UIApplication *)application {
  SoundPlayer::instance()->syncAudioSessionForITunes();
  SoundPlayer::instance()->duckAudioFromITunes(true);

  [viewController_ start];
  viewController_.gameEngine->ClearTouches();
}

- (void)applicationWillTerminate:(UIApplication *)application {
  [viewController_ stop];
}

- (UIWindow *)window {
  return viewController_.window;
}

@end
