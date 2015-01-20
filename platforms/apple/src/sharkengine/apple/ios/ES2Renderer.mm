//
//  ES2Renderer.m
//  SharkEngine
//
//  Created by Jon Sharkey on 2010-04-10.
//  Copyright 2010 Sharkable. All rights reserved.
//

#import "ES2Renderer.h"
#import "shark_engine.h"

// uniform index
enum {
  UNIFORM_TRANSLATE,
  NUM_UNIFORMS
};
GLint uniforms[NUM_UNIFORMS];

// attribute index
enum {
  ATTRIB_VERTEX,
  ATTRIB_COLOR,
  NUM_ATTRIBUTES
};

@interface ES2Renderer ()
- (BOOL)loadShaders;
- (BOOL)compileShader:(GLuint *)shader type:(GLenum)type file:(NSString *)file;
- (BOOL)linkProgram:(GLuint)prog;
- (BOOL)validateProgram:(GLuint)prog;
@end

@implementation ES2Renderer {
 @private
  EAGLContext *context_;

  // The pixel dimensions of the CAEAGLLayer
  GLint backingWidth_;
  GLint backingHeight_;

  // The OpenGL ES names for the framebuffer and renderbuffer used to render to this view
  GLuint defaultFramebuffer_;
  GLuint colorRenderbuffer_;

  GLuint program_;

  SharkEngine *gameEngine_;
}

// Create an OpenGL ES 2.0 context
- (id)init {
  self = [super init];
  if (self) {
    context_ = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];

    if (!context_ || ![EAGLContext setCurrentContext:context_] || ![self loadShaders]) {
      [self release];
      return nil;
    }

    // Create default framebuffer object. The backing will be allocated for the current layer in
    // -resizeFromLayer
    glGenFramebuffers(1, &defaultFramebuffer_);
    glGenRenderbuffers(1, &colorRenderbuffer_);
    glBindFramebuffer(GL_FRAMEBUFFER, defaultFramebuffer_);
    glBindRenderbuffer(GL_RENDERBUFFER, colorRenderbuffer_);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER,
                              colorRenderbuffer_);
  }

  return self;
}

- (void)dealloc {
  // Tear down GL
  if (defaultFramebuffer_) {
    glDeleteFramebuffers(1, &defaultFramebuffer_);
    defaultFramebuffer_ = 0;
  }

  if (colorRenderbuffer_) {
    glDeleteRenderbuffers(1, &colorRenderbuffer_);
    colorRenderbuffer_ = 0;
  }

  if (program_) {
    glDeleteProgram(program_);
    program_ = 0;
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
  // This application only creates a single context which is already set current at this point.
  // This call is redundant, but needed if dealing with multiple contexts.
  [EAGLContext setCurrentContext:context_];

  // This application only creates a single default framebuffer which is already bound at this
  // point. This call is redundant, but needed if dealing with multiple framebuffers.
  glBindFramebuffer(GL_FRAMEBUFFER, defaultFramebuffer_);
  glViewport(0, 0, backingWidth_, backingHeight_);

  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
}

- (void)finishRender {
  // This application only creates a single color renderbuffer which is already bound at this point.
  // This call is redundant, but needed if dealing with multiple renderbuffers.
  glBindRenderbuffer(GL_RENDERBUFFER, colorRenderbuffer_);
  [context_ presentRenderbuffer:GL_RENDERBUFFER];
}

- (BOOL)resizeFromLayer:(CAEAGLLayer *)layer {
  // Allocate color buffer backing based on the current layer size
  glBindRenderbuffer(GL_RENDERBUFFER, colorRenderbuffer_);
  [context_ renderbufferStorage:GL_RENDERBUFFER fromDrawable:layer];
  glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_WIDTH, &backingWidth_);
  glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_HEIGHT, &backingHeight_);

  if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
    NSLog(@"Failed to make complete framebuffer object %x",
          glCheckFramebufferStatus(GL_FRAMEBUFFER));
    return NO;
  }

  return YES;
}

#pragma mark - Private

- (BOOL)compileShader:(GLuint *)shader type:(GLenum)type file:(NSString *)file {
  GLint status;
  const GLchar *source;

  source = (GLchar *)[[NSString stringWithContentsOfFile:file
                                                encoding:NSUTF8StringEncoding
                                                   error:nil] UTF8String];
  if (!source) {
    NSLog(@"Failed to load vertex shader");
    return NO;
  }

  *shader = glCreateShader(type);
  glShaderSource(*shader, 1, &source, NULL);
  glCompileShader(*shader);

#if defined(DEBUG)
  GLint logLength;
  glGetShaderiv(*shader, GL_INFO_LOG_LENGTH, &logLength);
  if (logLength > 0) {
    GLchar *log = (GLchar *)malloc(logLength);
    glGetShaderInfoLog(*shader, logLength, &logLength, log);
    NSLog(@"Shader compile log:\n%s", log);
    free(log);
  }
#endif

  glGetShaderiv(*shader, GL_COMPILE_STATUS, &status);
  if (status == 0) {
    glDeleteShader(*shader);
    return NO;
  }

  return YES;
}

- (BOOL)linkProgram:(GLuint)prog {
  GLint status;

  glLinkProgram(prog);

#if defined(DEBUG)
  GLint logLength;
  glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &logLength);
  if (logLength > 0) {
      GLchar *log = (GLchar *)malloc(logLength);
      glGetProgramInfoLog(prog, logLength, &logLength, log);
      NSLog(@"Program link log:\n%s", log);
      free(log);
  }
#endif

  glGetProgramiv(prog, GL_LINK_STATUS, &status);
  if (status == 0)
      return NO;

  return YES;
}

- (BOOL)validateProgram:(GLuint)prog {
  GLint logLength, status;

  glValidateProgram(prog);
  glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &logLength);
  if (logLength > 0) {
      GLchar *log = (GLchar *)malloc(logLength);
      glGetProgramInfoLog(prog, logLength, &logLength, log);
      NSLog(@"Program validate log:\n%s", log);
      free(log);
  }

  glGetProgramiv(prog, GL_VALIDATE_STATUS, &status);
  if (status == 0) {
      return NO;
  }

  return YES;
}

- (BOOL)loadShaders {
  GLuint vertShader, fragShader;
  NSString *vertShaderPathname, *fragShaderPathname;

  // Create shader program
  program_ = glCreateProgram();

  // Create and compile vertex shader
  vertShaderPathname = [[NSBundle mainBundle] pathForResource:@"Shader" ofType:@"vsh"];
  if (![self compileShader:&vertShader type:GL_VERTEX_SHADER file:vertShaderPathname]) {
    NSLog(@"Failed to compile vertex shader");
    return NO;
  }

  // Create and compile fragment shader
  fragShaderPathname = [[NSBundle mainBundle] pathForResource:@"Shader" ofType:@"fsh"];
  if (![self compileShader:&fragShader type:GL_FRAGMENT_SHADER file:fragShaderPathname]) {
    NSLog(@"Failed to compile fragment shader");
    return NO;
  }

  // Attach vertex shader to program
  glAttachShader(program_, vertShader);

  // Attach fragment shader to program
  glAttachShader(program_, fragShader);

  // Bind attribute locations
  // this needs to be done prior to linking
  glBindAttribLocation(program_, ATTRIB_VERTEX, "position");
  glBindAttribLocation(program_, ATTRIB_COLOR, "color");

  // Link program
  if (![self linkProgram:program_]) {
    NSLog(@"Failed to link program: %d", program_);

    if (vertShader) {
      glDeleteShader(vertShader);
      vertShader = 0;
    }
    if (fragShader) {
      glDeleteShader(fragShader);
      fragShader = 0;
    }
    if (program_) {
      glDeleteProgram(program_);
      program_ = 0;
    }

    return NO;
  }

  // Get uniform locations
  uniforms[UNIFORM_TRANSLATE] = glGetUniformLocation(program_, "translate");

  // Release vertex and fragment shaders
  if (vertShader) {
    glDeleteShader(vertShader);
  }
  if (fragShader) {
    glDeleteShader(fragShader);
  }

  return YES;
}

@end
