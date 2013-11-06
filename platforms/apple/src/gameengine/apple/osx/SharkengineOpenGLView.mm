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
#include "gameengine/apple/osx/AppDelegate.h"

@interface SharkengineOpenGLView ()
- (CGFloat)scaleFactor;
- (BOOL)isFullScreen;
- (NSSize)defaultWindowSize;
- (void)updateEvent:(NSTimer *)timer;
- (void)start;
- (void)stop;
@end

@implementation SharkengineOpenGLView

- (void)prepareOpenGL {
  if (os_x_version() >= 107) {
    [self setWantsBestResolutionOpenGLSurface:YES];
  }

  // The original XIB view size determines the render size.
  windowSize_ = [self defaultWindowSize];
  screenScale_ = [self scaleFactor];
  renderSize_ = screen_size_make(windowSize_.width * screenScale_,
                                 windowSize_.height * screenScale_);

  // TODO should this really be here?
  gameEngine_ = new GameEngine();
  gameEngine_->platform().set_screen_size_group(Platform::kScreenSizeGroupPC);
  gameEngine_->platform().set_os_group(Platform::kOSGroupOSX);
  gameEngine_->platform().set_input_group(Platform::kInputGroupPC);
  if (screenScale_ == 1.0) {
    gameEngine_->platform().set_texture_group(Platform::kTextureGroupPCHighRes);
  } else {
    gameEngine_->platform().set_texture_group(Platform::kTextureGroupPCUltraHighRes);
  }

  gameEngine_->set_asset_reader_factory_module(
      sp<AssetReaderFactoryModule>(new OSXAssetReaderFactoryModule()));
  gameEngine_->set_persistence_module(sp<PersistenceModule>(new ApplePersistenceModule()));
  gameEngine_->set_input_module(sp<InputModule>(new OSXInputModule()));
  gameEngine_->set_sound(sp<SharkSound::SoundController>(new SharkSound::AppleSoundController()));

  gameEngine_->set_screen_size(renderSize_);

  sharkengine_init(gameEngine_);

  Texture2D::SetScreenHeight(renderSize_.height);

  glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_CULL_FACE);
  glEnable(GL_BLEND);
  glEnable(GL_TEXTURE_2D);
  glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, renderSize_.width, 0, renderSize_.height, -1, 1);

  glMatrixMode(GL_MODELVIEW);

  // Set swap interval for double buffering.
  GLint swapInt = 1;
  [[self openGLContext] setValues:&swapInt forParameter:NSOpenGLCPSwapInterval];

  [self start];
  [self performSelector:@selector(reshape) withObject:nil afterDelay:0.1];
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
  if (!NSEqualRects(self.frame, self.superview.frame)) {
    self.frame = self.superview.frame;
  }
  float screenWidthFloat = self.frame.size.width;
  float screenHeightFloat = self.frame.size.height;
  float viewportWidthFloat = screenHeightFloat * windowSize_.width / windowSize_.height;
  float viewportHeightFloat = screenHeightFloat;
  if (viewportWidthFloat > screenWidthFloat) {
    viewportWidthFloat = screenWidthFloat;
    viewportHeightFloat = screenWidthFloat * windowSize_.height / windowSize_.width;
  }

  viewportX_ = (int)((screenWidthFloat - viewportWidthFloat) / 2);
  viewportY_ = (int)((screenHeightFloat - viewportHeightFloat) / 2);
  viewportWidth_ = (int)viewportWidthFloat;
  viewportHeight_ = (int)viewportHeightFloat;
  glViewport(viewportX_ * screenScale_, viewportY_ * screenScale_, viewportWidth_ * screenScale_,
             viewportHeight_ * screenScale_);
}

- (BOOL)acceptsFirstResponder {
  return YES;
}

- (GamePoint)gamePointFromScreenPoint:(NSPoint)point {
  return game_point_make((point.x - viewportX_) * windowSize_.width / viewportWidth_,
                         windowSize_.height - (point.y - viewportY_) * windowSize_.height /
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

- (void)windowDidChangeBackingProperties:(NSNotification *)notification {
  screenScale_ = [self scaleFactor];
  // TODO HACK. This seems needed, otherwise if you move the window from a retina screen to a
  // non retina screen, the shape of the image can be wrong.
  [self performSelector:@selector(reshape) withObject:nil afterDelay:0.1];
}


#pragma mark - private

- (CGFloat)scaleFactor {
  if (os_x_version() <= 106) {
    return 1.0;
  }
  return self.window.backingScaleFactor;
}

- (BOOL)isFullScreen {
  return ([self.window styleMask] & NSFullScreenWindowMask) == NSFullScreenWindowMask;
}

- (NSSize)defaultWindowSize {
  NSString *xibFilename = [[NSBundle mainBundle] objectForInfoDictionaryKey:@"NSMainNibFile"];
  if ([xibFilename isEqualToString:@"MainMenu-Portrait"]) {
    return NSMakeSize(768, 1024);
  } else if ([xibFilename isEqualToString:@"MainMenu-Landscape"]) {
    return NSMakeSize(1136, 640);
  }
  shark_assert(false, "Couldn't figure out game orientation.");
  return NSMakeSize(0, 0);
}

- (void)updateEvent:(NSTimer *)timer {
  if (gameEngine_) {
    gameEngine_->Update();
  }
  [self setNeedsDisplay:YES];
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
