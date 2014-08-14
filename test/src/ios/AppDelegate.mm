//
//  AppDelegate.m
//  SharkEngine
//
//  Created by Jonathan Sharkey on 2/12/13.
//  Copyright Sharkable 2013. All rights reserved.
//

#import "ios/AppDelegate.h"

#import "gameengine/game_engine.h"
#import "ios/EAGLView.h"
#import "ios/ViewController.h"
#import "soundengine/sound_player.h"

#import "enginetest/views/main_view.h"

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
  viewController_ = [[ViewController alloc] initWithGameSize:game_size_make(320, 480)];
  sp<EngineView> rootView = sp<EngineView>(new MainView(viewController_.gameEngine));
  viewController_.gameEngine->PushView(rootView);

  return YES;
}

- (void)applicationWillResignActive:(UIApplication *)application {
  [viewController_ stop];
}

- (void)applicationDidBecomeActive:(UIApplication *)application {
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
