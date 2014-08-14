//
//  SharkengineOpenGLView.m
//  Air Hockey
//
//  Created by Jon Sharkey on 2013-07-29.
//  Copyright (c) 2013 Jon Sharkey. All rights reserved.
//

#import "SharkengineOpenGLView.h"

#include "sharksound/apple/AppleSoundController.h"

#include "sharkengine/game_engine.h"
#include "sharkengine/platform.h"
#include "sharkengine/apple/modules/ApplePersistenceModule.h"
#include "sharkengine/apple/modules/osx/OSXAssetReaderFactoryModule.h"
#include "sharkengine/apple/modules/osx/OSXInputModule.h"
#include "sharkengine/apple/osx/AppDelegate.h"
#include "sharkengine/input/input_event.h"

@implementation SharkengineOpenGLView

- (void)prepareOpenGL {
#if SE_APP_DISABLE_PC_ULTRA_HIGH_RES
#else
  if (os_x_version() >= 107) {
    [self setWantsBestResolutionOpenGLSurface:YES];
  }
#endif

  // The original XIB view size determines the render size.
  windowSize_ = [self defaultWindowSize];
  screenScale_ = [self scaleFactor];
  renderSize_ = ScreenSize(windowSize_.width * screenScale_, windowSize_.height * screenScale_);

  if (!didStart_) {
    [self start];
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

// Without this, moving the window to a screen where the scale changes will cause the game to be
// misshapen.
- (void)update {
  [super update];
  [self reshape];
}

- (BOOL)acceptsFirstResponder {
  return YES;
}

- (GamePoint)gamePointFromScreenPoint:(NSPoint)point {
  return GamePoint((point.x - viewportX_) * windowSize_.width / viewportWidth_,
                   windowSize_.height - (point.y - viewportY_) * windowSize_.height /
                       viewportHeight_);
}

- (void)mouseDown:(NSEvent *)theEvent {
  NSPoint mouseLocation = [theEvent locationInWindow];
  InputEvent event(InputEvent::kActionDown, InputEvent::kIdMouseButton0,
                   [self gamePointFromScreenPoint:mouseLocation]);
  gameEngine_->input_manager().AddEvent(event);
}

- (void)mouseDragged:(NSEvent *)theEvent {
  NSPoint mouseLocation = [theEvent locationInWindow];
  InputEvent event(InputEvent::kActionMove, InputEvent::kIdMouseButton0,
                   [self gamePointFromScreenPoint:mouseLocation]);
  gameEngine_->input_manager().AddEvent(event);

  // A drag is both a movement for kIdMouseButton0 and a mouse delta.
  [self mouseMoved:theEvent];
}

- (void)mouseUp:(NSEvent *)theEvent {
  NSPoint mouseLocation = [theEvent locationInWindow];
  InputEvent event(InputEvent::kActionUp, InputEvent::kIdMouseButton0,
                   [self gamePointFromScreenPoint:mouseLocation]);
  gameEngine_->input_manager().AddEvent(event);
}

// TODO It is more reasonable to expect this to be a pointer position. Rethink mouse input.
// IDEA: mouse visible and invisible mode. In invisible mode you get deltas, in visible mode you
//     get cursor positions.
- (void)mouseMoved:(NSEvent *)theEvent {
  InputEvent event(InputEvent::kActionMove, InputEvent::kIdMouse,
                   GamePoint(theEvent.deltaX, theEvent.deltaY));
  gameEngine_->input_manager().AddEvent(event);
  if (!CGCursorIsVisible()) {
    NSRect windowFrame = self.window.frame;
    CGPoint windowCenter = CGPointMake(NSMidX(windowFrame), NSMidY(windowFrame));
    CGDisplayMoveCursorToPoint(kCGDirectMainDisplay, windowCenter);
  }
}

- (void)considerAddingKeyWithEvent:(NSEvent *)theEvent action:(InputEvent::Action)action {
  // Allow Esc to remove full screen. In windowed mode, it gets passed to the game.
  if ([self isFullScreen] && theEvent.keyCode == 0x35 /* Esc */) {
    [super keyDown:theEvent];
  } else {
    if ([theEvent isARepeat]) {
      return;
    }

    InputEvent::Id input_id = InputEvent::kIdNone;
    switch (theEvent.keyCode) {
      case 0x31:
        input_id = InputEvent::kIdKeyboardSpace;
        break;
      case 0x35:
        input_id = InputEvent::kIdKeyboardEsc;
        break;
    }

    if (input_id == InputEvent::kIdNone) {
      return;
    }

    InputEvent event(action, input_id);
    gameEngine_->input_manager().AddEvent(event);
  }
}

- (void)keyDown:(NSEvent *)theEvent {
  [self considerAddingKeyWithEvent:theEvent action:InputEvent::kActionDown];
}

- (void)keyUp:(NSEvent *)theEvent {
  [self considerAddingKeyWithEvent:theEvent action:InputEvent::kActionUp];
}


#pragma mark - NSWindowDelegate

- (void)windowDidResignMain:(NSNotification *)notification {
  [self pause];
}

- (void)windowDidBecomeMain:(NSNotification *)notification {
  [self resume];
}

- (void)windowDidResize:(NSNotification *)notification {
  self.frame = self.superview.frame;
}

- (void)windowDidChangeBackingProperties:(NSNotification *)notification {
  screenScale_ = [self scaleFactor];
}

- (void)windowWillEnterFullScreen:(NSNotification *)notification {
  [self pause];
}

- (void)windowWillExterFullScreen:(NSNotification *)notification {
  [self pause];
}


#pragma mark - private

- (CGFloat)scaleFactor {
#if SE_APP_DISABLE_PC_ULTRA_HIGH_RES
  return 1.0;
#else
  if (os_x_version() <= 106) {
    return 1.0;
  }
  return self.window.backingScaleFactor;
#endif
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

- (void)setUpGameEngine {
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
  
  sharkengine_init(*gameEngine_);
}

- (void)setUpOpenGL {
  // We need a context created in the game thread.
  NSOpenGLContext *newContext =
      [[NSOpenGLContext alloc] initWithFormat:self.pixelFormat shareContext:nil];
  [self setOpenGLContext:newContext];
  [newContext setView:self];

  glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_CULL_FACE);
  glEnable(GL_BLEND);
  glEnable(GL_TEXTURE_2D);
  glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, renderSize_.width, renderSize_.height, 0, -1, 1);

  glMatrixMode(GL_MODELVIEW);

  // Set swap interval for double buffering.
  GLint swapInt = 1;
  [[self openGLContext] setValues:&swapInt forParameter:NSOpenGLCPSwapInterval];
}

- (void)runGameLoop {
  [self setUpOpenGL];
  [self setUpGameEngine];

  double last_system_time = CACurrentMediaTime();
  double accumulator = 0;
  static const double kTimeDelta = 1.0 / 60.0;

  [[NSThread currentThread] setThreadPriority:1.0];

  while (true) {
    // TODO use mach_absolute_time instead.
    double current_system_time = CACurrentMediaTime();
    double time_diff = current_system_time - last_system_time;
    last_system_time = current_system_time;
    accumulator += time_diff;

    while (accumulator >= kTimeDelta) {
      gameEngine_->Update();
      accumulator -= kTimeDelta;
    }

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
}

- (void)start {
  didStart_ = YES;
  [NSThread detachNewThreadSelector:@selector(runGameLoop) toTarget:self withObject:nil];
}

- (void)pause {
// TODO  gameEngine_->NotifyPause();
}

- (void)resume {
  // TODO ? (think about pause / resume semantics.)
}

@end
