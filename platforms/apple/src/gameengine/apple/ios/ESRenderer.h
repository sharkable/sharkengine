//
//  ESRenderer.h
//  GameEngine
//
//  Created by Jon Sharkey on 2010-04-10.
//  Copyright 2010 Sharkable. All rights reserved.
//

#import <QuartzCore/QuartzCore.h>

#import <OpenGLES/EAGL.h>
#import <OpenGLES/EAGLDrawable.h>

class GameEngine;

@protocol ESRenderer<NSObject>

- (void)setUpRender;
- (void)finishRender;
- (BOOL)resizeFromLayer:(CAEAGLLayer *)layer;

@end
