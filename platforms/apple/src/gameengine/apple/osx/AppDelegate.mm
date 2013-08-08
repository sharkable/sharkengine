//
//  AppDelegate.m
//  Air Hockey
//
//  Created by Jon Sharkey on 7/26/13.
//  Copyright (c) 2013 Jon Sharkey. All rights reserved.
//

#import "AppDelegate.h"

#import "gameengine/game_engine.h"
#import "gameengine/apple/modules/AppleGameEngineFactory.h"
#import "gameengine/apple/modules/AppleLocalStore.h"

#import "SharkengineOpenGLVIew.h"
#import "SharkengineViewController.h"

@interface  AppDelegate()
@property (nonatomic,strong) IBOutlet SharkengineViewController *sharkengineViewController;
@end

@implementation AppDelegate {
  GameEngine *gameEngine_;
  NSTimer *gameTimer_;
}

- (void)dealloc {
  delete gameEngine_;
  [gameTimer_ release];
  [super dealloc];
}


- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
  // 1. Create the master View Controller
  self.sharkengineViewController = [[SharkengineViewController alloc] initWithNibName:@"SharkengineViewController" bundle:nil];

  // 2. Add the view controller to the Window's content view
  [self.window.contentView addSubview:self.sharkengineViewController.view];
  self.sharkengineViewController.view.frame = ((NSView*)self.window.contentView).bounds;

  [self performSelector:@selector(foo) withObject:nil afterDelay:0.1];
}


- (void)foo {
  gameEngine_ = new GameEngine();
  gameEngine_->set_platform_type(kPlatformTypeTablet);
  gameEngine_->set_platform_resolution(kPlatformResolutionLow);
  gameEngine_->set_local_store(sp<LocalStore>(new AppleLocalStore()));

  NSTimeInterval interval = (NSTimeInterval)(1.0 / 60.0);
  gameTimer_ = [[NSTimer scheduledTimerWithTimeInterval:interval
                                                 target:self
                                               selector:@selector(update)
                                               userInfo:nil
                                                repeats:YES] retain];

  gameEngine_->set_screen_size(screen_size_make(768, 1024));
  gameEngine_->set_factory(sp<GameEngineFactory>(new AppleGameEngineFactory()));

  sharkengine_init(gameEngine_);

  Texture2D::SetScreenHeight(1024);
  glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_CULL_FACE);
  glEnable(GL_BLEND);
  glEnable(GL_TEXTURE_2D);
  glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);

  [SharkengineOpenGLView setGameEngine:gameEngine_];
}

- (void)update {
  gameEngine_->Update();
  [self.sharkengineViewController.view setNeedsDisplay:YES];
}

@end
