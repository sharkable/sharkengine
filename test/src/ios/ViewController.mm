//
//  ViewController.m
//  AirHockey
//
//  Created by Jonathan Sharkey on 4/1/12.
//  Copyright (c) 2012 Sharkable. All rights reserved.
//

#import "ViewController.h"

#import "EAGLView.h"
#import "game_engine.h"
#import "GameTimer.h"
#import "GameTouchWindow.h"
#import "ios/AdEngineIOS.h"
#import "main_view.h"
#import "texture2d.h"

@implementation ViewController {
 @private
  EAGLView *view_;
  GameTimer *gameTimer_;
  GameTouchWindow *gameTouchWindow_;

  GameEngine *game_engine_;
  sp<EngineView> root_view_;
};

@synthesize window = gameTouchWindow_, game_engine = game_engine_;

- (id)init {
  self = [super init];
  if (self) {
    CGRect screenSize = [[UIScreen mainScreen] bounds];
    gameTouchWindow_ = [[GameTouchWindow alloc] initWithFrame:screenSize];
    [gameTouchWindow_ addSubview:self.view];
    [gameTouchWindow_ makeKeyAndVisible];

    game_engine_ = new GameEngine();
    game_engine_->set_ad_engine(sp<AdEngine>(new AdEngineIOS(self)));

    CGSize size = [UIScreen mainScreen].bounds.size;
    CGFloat scale = [UIScreen mainScreen].scale;
    game_engine_->SetScreenSize(screen_size_make(size.width * scale, size.height * scale),
                                game_size_make(320, 480));

    root_view_.reset(new MainView(sp<GameEngine>(game_engine_)));
    game_engine_->PushView(root_view_);
    gameTimer_ = [[GameTimer alloc] initWithTarget:self selector:@selector(update)];
    gameTouchWindow_.gameEngine = game_engine_;    
  }
  return self;
}

- (void)dealloc {
  delete game_engine_;

  [view_ release];
  [gameTimer_ release];
  [gameTouchWindow_ release];

  [super dealloc];
}

- (void)start {
  [gameTimer_ start];
}

- (void)stop {  
  [gameTimer_ stop];
}

#pragma mark - UIViewController

- (void)loadView {
  // TODO: Consider handling viewDidUnload: to free memory.
  if (!view_) {
    view_ = [[EAGLView alloc] initWithFrame:gameTouchWindow_.frame];
  }
  self.view = view_;
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
  return (interfaceOrientation == UIInterfaceOrientationPortrait ||
          interfaceOrientation == UIInterfaceOrientationPortraitUpsideDown);
}

#pragma mark - Private

- (void)update {
  game_engine_->Update();
  [view_ setUpRender];
  game_engine_->Render();
  [view_ finishRender];
}

@end
