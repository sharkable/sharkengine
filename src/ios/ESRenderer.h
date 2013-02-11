//
//  ESRenderer.h
//  AirHockey
//
//  Created by Jonathan Sharkey on 10-04-10.
//  Copyright Sharkable 2010. All rights reserved.
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
