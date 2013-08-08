//
//  SharkengineOpenGLView.m
//  Air Hockey
//
//  Created by Jon Sharkey on 2013-07-29.
//  Copyright (c) 2013 Jon Sharkey. All rights reserved.
//

#import "SharkengineOpenGLView.h"

#include <OpenGL/gl.h>

#include "gameengine/game_engine.h"
#include "gameengine/apple/modules/AppleGameEngineFactory.h"
#include "gameengine/apple/modules/AppleLocalStore.h"

static GameEngine *gameEngine_ = NULL;

@implementation SharkengineOpenGLView {
  NSTimer *timer_;
  int viewportX_;
  int viewportY_;
  int viewportWidth_;
  int viewportHeight_;
}

- (id)init {
  self = [super init];
  if (self) {
    viewportX_ = 0;  // TODO maybe not needed. Is |resize| always called?
    viewportY_ = 0;
    viewportWidth_ = 768;
    viewportHeight_ = 1024;
  }
  return self;
}

- (id)initWithFrame:(NSRect)frameRect {
  self = [super initWithFrame:frameRect];
  if (self) {
    [self setAutoresizingMask:NSViewWidthSizable | NSViewHeightSizable];
  }
  return self;
}

- (void)prepareOpenGL {
  // TODO should this really be here?
  gameEngine_ = new GameEngine();
  gameEngine_->set_platform_type(kPlatformTypeTablet);
  gameEngine_->set_platform_resolution(kPlatformResolutionLow);
  gameEngine_->set_local_store(sp<LocalStore>(new AppleLocalStore()));

  gameEngine_->set_screen_size(screen_size_make(768, 1024));
  gameEngine_->set_factory(sp<GameEngineFactory>(new AppleGameEngineFactory()));

  sharkengine_init(gameEngine_);

  Texture2D::SetScreenHeight(1024);

  [SharkengineOpenGLView setGameEngine:gameEngine_];

  glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_CULL_FACE);
  glEnable(GL_BLEND);
  glEnable(GL_TEXTURE_2D);
  glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);

  glViewport(viewportX_, viewportY_, viewportWidth_, viewportHeight_);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, 768, 0, 1024, -1, 1);

  glMatrixMode(GL_MODELVIEW);

  // Set swap interval for double buffering.
  GLint swapInt = 1;
  [[self openGLContext] setValues:&swapInt forParameter:NSOpenGLCPSwapInterval];
}

- (void)drawRect:(NSRect)dirtyRect {
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();

  if (gameEngine_) {
    gameEngine_->Render();
  }

  [[self openGLContext] flushBuffer];

  int err;
  if ((err = glGetError()) != 0) {
    NSLog(@"glGetError(): %d", err);
  }
}

- (void)reshape {
  float screenWidthFloat = [self frame].size.width;
  float screenHeightFloat = [self frame].size.height;
  float viewportWidthFloat = screenHeightFloat * 768.0 / 1024.0;
  float viewportHeightFloat = screenHeightFloat;
  if (viewportWidthFloat > screenWidthFloat) {
    viewportWidthFloat = screenWidthFloat;
    viewportHeightFloat = screenWidthFloat * 1024.0 / 768.0;
  }

  viewportX_ = (int)((screenWidthFloat - viewportWidthFloat) / 2);
  viewportY_ = (int)((screenHeightFloat - viewportHeightFloat) / 2);
  viewportWidth_ = (int)viewportWidthFloat;
  viewportHeight_ = (int)viewportHeightFloat;
  glViewport(viewportX_, viewportY_, viewportWidth_, viewportHeight_);
}

- (BOOL)acceptsFirstResponder {
  return YES;
}

- (GamePoint)gamePointFromScreenPoint:(CGPoint)point {
  return game_point_make((point.x - viewportX_) * 768.0 / viewportWidth_,
                         1024.0 - (point.y - viewportY_) * 1024.0 / viewportHeight_);
}

- (void)mouseDown:(NSEvent *)theEvent {
  NSPoint mouseLocation = [theEvent locationInWindow];
  Touch t;
  t.set_location([self gamePointFromScreenPoint:mouseLocation]);
  t.set_identifier((void *)1);
  gameEngine_->AddTouchBegan(t);
}

- (void)mouseDragged:(NSEvent *)theEvent {
  NSPoint mouseLocation = [theEvent locationInWindow];
  Touch t;
  t.set_location([self gamePointFromScreenPoint:mouseLocation]);
  t.set_identifier((void *)1);
  gameEngine_->AddTouchMoved(t);
}

- (void)mouseUp:(NSEvent *)theEvent {
  NSPoint mouseLocation = [theEvent locationInWindow];
  Touch t;
  t.set_location([self gamePointFromScreenPoint:mouseLocation]);
  t.set_identifier((void *)1);
  gameEngine_->AddTouchEnded(t);
}

- (void)mouseMoved:(NSEvent *)theEvent {
  gameEngine_->AddMouseDelta(theEvent.deltaX, theEvent.deltaY);
}

+ (void)setGameEngine:(GameEngine *)gameEngine {
  gameEngine_ = gameEngine;
}


// NSWindowDelegate

- (void)windowDidResignMain:(NSNotification *)notification {
  [timer_ invalidate];

  // TODO freeze, pause
  [self setNeedsDisplay:YES];
}

- (void)windowDidBecomeMain:(NSNotification *)notification {
  // TODO continue game.
  [self setNeedsDisplay:YES];

  timer_ = [NSTimer timerWithTimeInterval:1.0/60.0
                                   target:self
                                 selector:@selector(timerEvent:)
                                 userInfo:nil
                                  repeats:YES];

  [[NSRunLoop mainRunLoop] addTimer:timer_ forMode:NSDefaultRunLoopMode];
}

- (void)timerEvent:(NSTimer *)t {
  if (gameEngine_) {
    gameEngine_->Update();
  }
  [self setNeedsDisplay:YES];
}

@end
