//
//  ES1Renderer.m
//  GameEngine
//
//  Created by Jon Sharkey on 2010-04-10.
//  Copyright 2010 Sharkable. All rights reserved.
//

#import "gameengine/apple/ios/ES1Renderer.h"

#import "gameengine/opengl/texture2d.h"

@implementation ES1Renderer {
 @private
  EAGLContext *context_;

  // The pixel dimensions of the CAEAGLLayer
  GLint backingWidth_;
  GLint backingHeight_;

  // The OpenGL ES names for the framebuffer and renderbuffer used to render to this view
  GLuint defaultFramebuffer_;
  GLuint colorRenderbuffer_;
  GLuint depthRenderbuffer_;
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
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

- (void)finishRender {
  [context_ presentRenderbuffer:GL_RENDERBUFFER_OES];
}

- (BOOL)resizeFromLayer:(CAEAGLLayer *)layer {
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

  // TODO how do I do this properly? I can't make this happen AFTER the next section (to get the
  // width and heigh THAT way.)
  CGSize layerSize = layer.visibleRect.size;
  float scale = [UIScreen mainScreen].scale;
  glGenRenderbuffers(1, &depthRenderbuffer_);
  glBindRenderbuffer(GL_RENDERBUFFER, depthRenderbuffer_);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, layerSize.width * scale,
                        layerSize.height * scale);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER,
                            depthRenderbuffer_);

  // Allocate color buffer backing based on the current layer size
  glBindRenderbufferOES(GL_RENDERBUFFER_OES, colorRenderbuffer_);
  [context_ renderbufferStorage:GL_RENDERBUFFER_OES fromDrawable:layer];
  glGetRenderbufferParameterivOES(GL_RENDERBUFFER_OES, GL_RENDERBUFFER_WIDTH_OES, &backingWidth_);
  glGetRenderbufferParameterivOES(GL_RENDERBUFFER_OES, GL_RENDERBUFFER_HEIGHT_OES, &backingHeight_);
  Texture2D::SetScreenHeight(backingHeight_);

  glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_CULL_FACE);
  glEnable(GL_BLEND);
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_POLYGON_OFFSET_FILL);
  glDisable(GL_DEPTH_TEST);
  glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);

  if (glCheckFramebufferStatusOES(GL_FRAMEBUFFER_OES) != GL_FRAMEBUFFER_COMPLETE_OES) {
    NSLog(@"Failed to make complete framebuffer object %x",
          glCheckFramebufferStatusOES(GL_FRAMEBUFFER_OES));
    return NO;
  }

  return YES;
}

@end
