//
//  SharkengineOpenGLView.h
//  Air Hockey
//
//  Created by Jon Sharkey on 2013-07-29.
//  Copyright (c) 2013 Jon Sharkey. All rights reserved.
//

@interface SharkengineOpenGLView : NSOpenGLView<NSWindowDelegate> {
  NSTimer *timer_;
  int viewportX_;
  int viewportY_;
  int viewportWidth_;
  int viewportHeight_;
}

@end
