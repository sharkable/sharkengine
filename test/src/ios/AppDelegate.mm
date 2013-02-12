//
//  AppDelegate.m
//  GameEngine
//
//  Created by Jonathan Sharkey on 2/12/13.
//  Copyright Sharkable 2013. All rights reserved.
//

#import "AppDelegate.h"
#import "EAGLView.h"
#import "FlurryAnalytics.h"
#import "game_engine.h"
#import "sound_player.h"
#import "main_view.h"
#import "ViewController.h"

@interface AppDelegate ()
- (void)initAudio:(SoundInitializationDelegate *)delegate;
@end

@implementation AppDelegate {
 @private
  ViewController *viewController_;
}

- (void)dealloc {
  [viewController_ release];

  [super dealloc];
}

- (void)initAudio:(SoundInitializationDelegate *)delegate {
  NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
  
// TODO  SoundPlayer::instance()->syncAudioSessionForITunes();
  SoundPlayer::instance()->initializeWithDelegate(delegate);
  SoundPlayer::instance()->setSoundEffectsOn(true);
  
  [pool release];
}  

#pragma mark - UIApplicationDelegate

- (BOOL)application:(UIApplication *)application
    didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
  viewController_ = [[ViewController alloc] init];
  
  return YES;
}

- (void)applicationWillResignActive:(UIApplication *)application {
  [viewController_ stop];
}

- (void)applicationDidBecomeActive:(UIApplication *)application {
  [viewController_ start];
  viewController_.game_engine->ClearTouches();
}

- (void)applicationWillTerminate:(UIApplication *)application {
  [viewController_ stop];
}

- (UIWindow *)window {
  return viewController_.window;
}

@end
