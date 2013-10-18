//
//  label.cc
//  GameEngine
//
//  Created by Jon Sharkey on 2010-09-18.
//  Copyright 2013 Sharkable. All rights reserved.
//

#include "gameengine/font.h"
#include "gameengine/entities/label.h"

static Font * font__ = NULL;

Label::Label(GameEngine *game_engine, GamePoint position)
    : Animatable(position) {
  if (!font__) {
    font__ = new Font(game_engine, "font");
  }
}

#pragma mark - ViewEntity

void Label::Render(GamePoint offset) {
  GamePoint render_point = position() + offset;
  for (int i = 0; i < text_.length(); i++) {
    char c = text_[i];
    if (c == '\n') {
      render_point = game_point_make(position().x + offset.x,
                                     render_point.y + font__->GlyphHeight());
    } else {
      font__->RenderGlyph(c, render_point);
      render_point.x += font__->GlyphWidth(c);
    }
  }
}
