//
//  EAGLView.h
//  SharkEngine
//
//  Created by Jon Sharkey on 2010-04-10.
//  Copyright 2010 Sharkable. All rights reserved.
//

#import <UIKit/UIKit.h>

// This class wraps the CAEAGLLayer from CoreAnimation into a convenient UIView subclass.
// The view content is basically an EAGL surface you render your OpenGL scene into.
// Note that setting the view non-opaque will only work if the EAGL surface has an alpha channel.
@interface EAGLView : UIView

// Call once at the start of the game thread.
- (void)initRenderer;

// Call these at the start and end of rendering a frame.
// Call |setUpRender| to clear the scene and set up the coordinate system.
// After that, make OpenGL calls to render all of the objects within the scene.
// Call |finishRender| to present the buffer.
- (void)setUpRender;
- (void)finishRender;

@end
