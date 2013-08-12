//
//  AppDelegate.m
//  Air Hockey
//
//  Created by Jon Sharkey on 7/26/13.
//  Copyright (c) 2013 Jon Sharkey. All rights reserved.
//

#import "AppDelegate.h"

#import "SharkengineOpenGLView.h"

@implementation AppDelegate

@synthesize window;
@synthesize openGLView;

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
  [self.window setAcceptsMouseMovedEvents:YES];
  [self.window setDelegate:self.openGLView];
}

- (void)applicationDidBecomeActive:(NSNotification *)aNotification {
  [self.window makeKeyAndOrderFront:self];
}

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)theApplication {
  return YES;
}

@end
