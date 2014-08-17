//
//  AppDelegate.m
//  Air Hockey
//
//  Created by Jon Sharkey on 7/26/13.
//  Copyright (c) 2013 Jon Sharkey. All rights reserved.
//

#import "AppDelegate.h"

#import <CoreServices/CoreServices.h>

#import "sharkengine/apple/osx/SharkengineOpenGLView.h"

@implementation AppDelegate

@synthesize window;
@synthesize openGLView;

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
  [self.window setAcceptsMouseMovedEvents:YES];
  [self.window setDelegate:self.openGLView];

  if (os_x_version() >= 107) {
    [self.window setCollectionBehavior:NSWindowCollectionBehaviorFullScreenPrimary];
  }
}

- (void)applicationDidBecomeActive:(NSNotification *)aNotification {
  [self.window makeKeyAndOrderFront:self];
}

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)theApplication {
  return YES;
}

@end

// Returns 106 for 10.6, 107 for 10.7, etc.
int os_x_version() {
  SInt32 major = 0;
  SInt32 minor = 0;
  Gestalt(gestaltSystemVersionMajor, &major);
  Gestalt(gestaltSystemVersionMinor, &minor);
  return major * 10 + minor;
}
