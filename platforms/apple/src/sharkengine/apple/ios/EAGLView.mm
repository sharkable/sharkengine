//
//  EAGLView.m
//  SharkEngine
//
//  Created by Jon Sharkey on 2010-04-10.
//  Copyright 2010 Sharkable. All rights reserved.
//

#import "EAGLView.h"

#import "ES1Renderer.h"
#import "ES2Renderer.h"
#import "ESRenderer.h"

@implementation EAGLView {
 @private
  id<ESRenderer> renderer_;
}

// You must implement this method
+ (Class)layerClass {
  return [CAEAGLLayer class];
}

- (id)initWithFrame:(CGRect)frame {
  self = [super initWithFrame:frame];
  if (self) {
    self.contentScaleFactor = [UIScreen mainScreen].scale;
    self.multipleTouchEnabled = YES;

    // Get the layer
    CAEAGLLayer *eaglLayer = (CAEAGLLayer *)self.layer;

    eaglLayer.opaque = YES;
    eaglLayer.drawableProperties =
        [NSDictionary dictionaryWithObjectsAndKeys:
         [NSNumber numberWithBool:NO], kEAGLDrawablePropertyRetainedBacking,
         kEAGLColorFormatRGBA8, kEAGLDrawablePropertyColorFormat,
         nil];

  }

  return self;
}

- (void)dealloc {
  [renderer_ release];

  [super dealloc];
}

- (void)initRenderer {
  renderer_ = [[ES2Renderer alloc] init];

  if (!renderer_) {
    renderer_ = [[ES1Renderer alloc] init];

    if (!renderer_) {
      [self release];
    }
  }
  [renderer_ resizeFromLayer:(CAEAGLLayer *)self.layer];
}

- (void)setUpRender {
  [renderer_ setUpRender];
}

- (void)finishRender {
  [renderer_ finishRender];
}

@end
