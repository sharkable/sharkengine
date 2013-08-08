//
//  AppDelegate.h
//  Air Hockey
//
//  Created by Jon Sharkey on 7/26/13.
//  Copyright (c) 2013 Jon Sharkey. All rights reserved.
//

@class SharkengineOpenGLView;

@interface AppDelegate : NSObject<NSApplicationDelegate>

@property (assign) IBOutlet NSWindow *window;
@property (assign) IBOutlet SharkengineOpenGLView *openGLView;

@end
