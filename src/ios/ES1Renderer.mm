//
//  ES1Renderer.m
//  AirHockey
//
//  Created by Jonathan Sharkey on 10-04-10.
//  Copyright Sharkable 2010. All rights reserved.
//

#import "ES1Renderer.h"

@implementation ES1Renderer {
 @private
  EAGLContext *context_;
  
  // The pixel dimensions of the CAEAGLLayer
  GLint backingWidth_;
  GLint backingHeight_;
  
  // The OpenGL ES names for the framebuffer and renderbuffer used to render to this view
  GLuint defaultFramebuffer_;
  GLuint colorRenderbuffer_;
}

// Create an OpenGL ES 1.1 context
- (id)init {
  self = [super init];
  if (self) {
    context_ = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES1];

    if (!context_ || ![EAGLContext setCurrentContext:context_]) {
        [self release];
        return nil;
    }

    // Create default framebuffer object. The backing will be allocated for the current layer in
    // -resizeFromLayer
    glGenFramebuffersOES(1, &defaultFramebuffer_);
    glGenRenderbuffersOES(1, &colorRenderbuffer_);
    glBindFramebufferOES(GL_FRAMEBUFFER_OES, defaultFramebuffer_);
    glBindRenderbufferOES(GL_RENDERBUFFER_OES, colorRenderbuffer_);
    glFramebufferRenderbufferOES(GL_FRAMEBUFFER_OES, GL_COLOR_ATTACHMENT0_OES, GL_RENDERBUFFER_OES,
                                 colorRenderbuffer_);
    
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);    
  }

  return self;
}

- (void)dealloc {
  // Tear down GL
  if (defaultFramebuffer_) {
    glDeleteFramebuffersOES(1, &defaultFramebuffer_);
    defaultFramebuffer_ = 0;
  }
  
  if (colorRenderbuffer_) {
    glDeleteRenderbuffersOES(1, &colorRenderbuffer_);
    colorRenderbuffer_ = 0;
  }
  
  // Tear down context
  if ([EAGLContext currentContext] == context_) {
    [EAGLContext setCurrentContext:nil];
  }
  
  [context_ release];
  context_ = nil;
  
  [super dealloc];
}

#pragma mark - ESRenderer

- (void)setUpRender {
  glViewport(0, 0, backingWidth_, backingHeight_);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrthof(0, backingWidth_, 0, backingHeight_, -1, 1);  

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
}

- (void)finishRender {
  [context_ presentRenderbuffer:GL_RENDERBUFFER_OES];
}

- (BOOL)resizeFromLayer:(CAEAGLLayer *)layer {  
  // Allocate color buffer backing based on the current layer size
  glBindRenderbufferOES(GL_RENDERBUFFER_OES, colorRenderbuffer_);
  [context_ renderbufferStorage:GL_RENDERBUFFER_OES fromDrawable:layer];
  glGetRenderbufferParameterivOES(GL_RENDERBUFFER_OES, GL_RENDERBUFFER_WIDTH_OES, &backingWidth_);
  glGetRenderbufferParameterivOES(GL_RENDERBUFFER_OES, GL_RENDERBUFFER_HEIGHT_OES, &backingHeight_);
  
  if (glCheckFramebufferStatusOES(GL_FRAMEBUFFER_OES) != GL_FRAMEBUFFER_COMPLETE_OES) {
    NSLog(@"Failed to make complete framebuffer object %x",
          glCheckFramebufferStatusOES(GL_FRAMEBUFFER_OES));
    return NO;
  }

  return YES;
}

@end
