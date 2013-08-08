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

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
  [self.window setDelegate:self.openGLView];
}

@end
