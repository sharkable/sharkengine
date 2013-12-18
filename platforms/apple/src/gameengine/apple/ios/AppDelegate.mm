//
//  AppDelegate.m
//  GameEngine
//
//  Created by Jon Sharkey on 2010-05-07.
//  Copyright 2010 Sharkable. All rights reserved.
//

#import "gameengine/apple/ios/AppDelegate.h"

#import "gameengine/apple/TypeUtil.h"
#import "gameengine/apple/ios/ViewController.h"
#import "gameengine/apple/thirdparty/ios/appirater/Appirater.h"
#import "gameengine/apple/thirdparty/ios/flurry/Flurry.h"
//#import "gameengine/modules/sound_player.h"
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
  // TODO make Appirater optional.
//  [Appirater setAppId:@"371905230"];
//  [Appirater setDaysUntilPrompt:1];
//  [Appirater setUsesUntilPrompt:6];
//  [Appirater setSignificantEventsUntilPrompt:-1];
//  [Appirater setTimeBeforeReminding:2];
//  [Appirater setDebug:NO];

  // TODO let the app set the Flurry id.
  NSString *appVersion = [[[NSBundle mainBundle] infoDictionary] objectForKey:@"CFBundleVersion"];
  [Flurry setAppVersion:appVersion];
  [Flurry startSession:@"4BYTHKQNVMS5J89XVZF6"];

  viewController_ = [[ViewController alloc] init];

//  SoundPlayer::instance()->syncAudioSessionForITunes();

//  [Appirater appLaunched:YES];

  return YES;
}

- (void)applicationWillEnterForeground:(UIApplication *)application {
  exit(0);
//  [Appirater appEnteredForeground:YES];
}

- (void)applicationWillResignActive:(UIApplication *)application {
  [viewController_ pause];
}

- (void)applicationDidBecomeActive:(UIApplication *)application {
  [viewController_ start];
  viewController_.gameEngine->ClearTouches();
}

- (void)applicationWillTerminate:(UIApplication *)application {
  [viewController_ pause];
}

- (UIWindow *)window {
  return viewController_.window;
}

@end
