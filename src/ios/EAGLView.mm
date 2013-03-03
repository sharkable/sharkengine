//
//  EAGLView.m
//  AirHockey
//
//  Created by Jonathan Sharkey on 10-04-10.
//  Copyright Sharkable 2010. All rights reserved.
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

    renderer_ = [[ES2Renderer alloc] init];

    if (!renderer_) {
      renderer_ = [[ES1Renderer alloc] init];

      if (!renderer_) {
        [self release];
        return nil;
      }
    }
    [renderer_ resizeFromLayer:(CAEAGLLayer *)self.layer];
  }

  return self;
}

- (void)dealloc {
  [renderer_ release];
  
  [super dealloc];
}

- (void)setUpRender {
  [renderer_ setUpRender];
}

- (void)finishRender {
  [renderer_ finishRender];
}

@end
