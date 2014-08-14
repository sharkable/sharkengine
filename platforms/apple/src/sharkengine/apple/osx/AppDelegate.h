//
//  AppDelegate.h
//  Air Hockey
//
//  Created by Jon Sharkey on 7/26/13.
//  Copyright (c) 2013 Jon Sharkey. All rights reserved.
//

@class SharkengineOpenGLView;

@interface AppDelegate : NSObject<NSApplicationDelegate> {
 @private
  IBOutlet NSWindow *window;
  IBOutlet SharkengineOpenGLView *openGLView;
}

@property (assign) IBOutlet NSWindow *window;
@property (assign) IBOutlet SharkengineOpenGLView *openGLView;

@end

// Returns 106 for 10.6, 107 for 10.7, etc.
int os_x_version();
