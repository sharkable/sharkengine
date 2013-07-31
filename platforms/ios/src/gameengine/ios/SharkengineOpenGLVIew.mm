//
//  SharkengineOpenGLView.m
//  Air Hockey
//
//  Created by Jon Sharkey on 2013-07-29.
//  Copyright (c) 2013 Jon Sharkey. All rights reserved.
//

#import "SharkengineOpenGLVIew.h"

#include <OpenGL/gl.h>

static GameEngine *gameEngine_ = NULL;

@implementation SharkengineOpenGLView

- (void)drawRect:(NSRect)bounds {
  glViewport(0, 0, 768, 1024);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, 768, 0, 1024, -1, 1);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  if (gameEngine_) {
    gameEngine_->Render();
  }
  glFlush();

  NSSize s;
  s.width = 2;
  s.height = 1;
  [self scaleUnitSquareToSize:s];
}

- (BOOL)acceptsFirstResponder {
  return YES;
}

- (void)mouseDown:(NSEvent *)theEvent {
  NSPoint mouseLocation = [theEvent locationInWindow];
  Touch t;
  t.set_location(game_point_make(mouseLocation.x, 1024 - mouseLocation.y));
  t.set_identifier((void *)1);
  gameEngine_->AddTouchBegan(t);
}

- (void)mouseDragged:(NSEvent *)theEvent {
  NSPoint mouseLocation = [theEvent locationInWindow];
  Touch t;
  t.set_location(game_point_make(mouseLocation.x, 1024 - mouseLocation.y));
  t.set_identifier((void *)1);
  gameEngine_->AddTouchMoved(t);
}

- (void)mouseUp:(NSEvent *)theEvent {
  NSPoint mouseLocation = [theEvent locationInWindow];
  Touch t;
  t.set_location(game_point_make(mouseLocation.x, 1024 - mouseLocation.y));
  t.set_identifier((void *)1);
  gameEngine_->AddTouchEnded(t);
}

+ (void)setGameEngine:(GameEngine *)gameEngine {
  gameEngine_ = gameEngine;
}

@end
