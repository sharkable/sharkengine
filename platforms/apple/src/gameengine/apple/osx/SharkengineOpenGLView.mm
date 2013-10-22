//
//  SharkengineOpenGLView.m
//  Air Hockey
//
//  Created by Jon Sharkey on 2013-07-29.
//  Copyright (c) 2013 Jon Sharkey. All rights reserved.
//

#import "SharkengineOpenGLView.h"

#include <OpenGL/gl.h>

#include "sharksound/apple/AppleSoundController.h"

#include "gameengine/game_engine.h"
#include "gameengine/platform.h"
#include "gameengine/apple/modules/ApplePersistenceModule.h"
#include "gameengine/apple/modules/osx/OSXAssetReaderFactoryModule.h"
#include "gameengine/apple/modules/osx/OSXInputModule.h"

@interface SharkengineOpenGLView ()
- (BOOL)isFullScreen;
- (void)updateEvent:(NSTimer *)timer;
- (void)start;
- (void)stop;
@end

@implementation SharkengineOpenGLView

- (void)prepareOpenGL {
  // The original XIB view size determines the render size.
  renderSize_.width = self.frame.size.width;
  renderSize_.height = self.frame.size.height;

  // TODO should this really be here?
  gameEngine_ = new GameEngine();
  gameEngine_->platform().set_screen_size_group(Platform::kScreenSizeGroupPC);
  gameEngine_->platform().set_os_group(Platform::kOSGroupOSX);
  gameEngine_->platform().set_input_group(Platform::kInputGroupPC);
  gameEngine_->platform().set_texture_group(Platform::kTextureGroupPCHighRes);

  gameEngine_->set_asset_reader_factory_module(
      sp<AssetReaderFactoryModule>(new OSXAssetReaderFactoryModule()));
  gameEngine_->set_persistence_module(sp<PersistenceModule>(new ApplePersistenceModule()));
  gameEngine_->set_input_module(sp<InputModule>(new OSXInputModule()));
  gameEngine_->set_sound(sp<SharkSound::SoundController>(new SharkSound::AppleSoundController()));

  gameEngine_->set_screen_size(screen_size_make(renderSize_.width, renderSize_.height));

  sharkengine_init(gameEngine_);

  Texture2D::SetScreenHeight(renderSize_.height);

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
  glOrtho(0, renderSize_.width, 0, renderSize_.height, -1, 1);

  glMatrixMode(GL_MODELVIEW);

  // Set swap interval for double buffering.
  GLint swapInt = 1;
  [[self openGLContext] setValues:&swapInt forParameter:NSOpenGLCPSwapInterval];

  [self start];
}

- (void)reshape {
  if (!NSEqualRects(self.frame, self.superview.frame)) {
    self.frame = self.superview.frame;
  }
  float screenWidthFloat = self.frame.size.width;
  float screenHeightFloat = self.frame.size.height;
  float viewportWidthFloat = screenHeightFloat * renderSize_.width / renderSize_.height;
  float viewportHeightFloat = screenHeightFloat;
  if (viewportWidthFloat > screenWidthFloat) {
    viewportWidthFloat = screenWidthFloat;
    viewportHeightFloat = screenWidthFloat * renderSize_.height / renderSize_.width;
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

- (GamePoint)gamePointFromScreenPoint:(NSPoint)point {
  return game_point_make((point.x - viewportX_) * renderSize_.width / viewportWidth_,
                         renderSize_.height - (point.y - viewportY_) * renderSize_.height /
                             viewportHeight_);
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
  if (!CGCursorIsVisible()) {
    NSRect windowFrame = self.window.frame;
    CGPoint windowCenter = CGPointMake(NSMidX(windowFrame), NSMidY(windowFrame));
    CGDisplayMoveCursorToPoint(kCGDirectMainDisplay, windowCenter);
  }
}

- (void)keyDown:(NSEvent *)theEvent {
  if ([self isFullScreen] && theEvent.keyCode == 0x35 /* Esc */) {
    [super keyDown:theEvent];
  } else {
    gameEngine_->AddKeyPressed(theEvent.keyCode);
  }
}


#pragma mark - NSWindowDelegate

- (void)windowDidResignMain:(NSNotification *)notification {
  [self stop];
}

- (void)windowDidBecomeMain:(NSNotification *)notification {
  [self start];
}

- (void)windowDidResize:(NSNotification *)notification {
  self.frame = self.superview.frame;
}


#pragma mark - private

- (BOOL)isFullScreen {
  return ([self.window styleMask] & NSFullScreenWindowMask) == NSFullScreenWindowMask;
}

- (void)updateEvent:(NSTimer *)timer {
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();

  if (gameEngine_) {
    gameEngine_->Update();
    gameEngine_->Render();
  }

  [[self openGLContext] flushBuffer];

  int err;
  if ((err = glGetError()) != 0) {
    NSLog(@"glGetError(): %d", err);
  }
}

- (void)start {
  if (timer_) {
    return;
  }
  [self setNeedsDisplay:YES];
  timer_ = [[NSTimer timerWithTimeInterval:1.0/60.0
                                    target:self
                                  selector:@selector(updateEvent:)
                                  userInfo:nil
                                   repeats:YES] retain];

  [[NSRunLoop mainRunLoop] addTimer:timer_ forMode:NSDefaultRunLoopMode];
}

- (void)stop {
  [timer_ invalidate];
  [timer_ release];
  timer_ = nil;

  gameEngine_->NotifyPause();
  gameEngine_->Update();
  [self setNeedsDisplay:YES];
}

@end
