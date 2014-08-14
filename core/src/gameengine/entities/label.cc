//
//  label.cc
//  GameEngine
//
//  Created by Jon Sharkey on 2010-09-18.
//  Copyright 2013 Sharkable. All rights reserved.
//

#include "gameengine/entities/label.h"

#include <cmath>

#include "gameengine/font.h"

static Font * font__ = NULL;

Label::Label(GameEngine &game_engine, GamePoint position)
    : Animatable(position),
      size_(kGameSizeZero) {
  if (!font__) {
    font__ = new Font(game_engine, "font");
  }
}

const std::string & Label::Text() {
  return text_;

}

void Label::SetText(const std::string &text) {
  text_ = text;
  size_ = CalculateSize();
}

GameRect Label::Rect() {
  return GameRect(position(), size_);
}


#pragma mark - Renderer

void Label::Render(CoordinateSystem const &coordinate_system) {
  GamePoint render_point = position();
  for (int i = 0; i < text_.length(); i++) {
    char c = text_[i];
    if (c == '\n') {
      render_point = GamePoint(position().x, render_point.y + font__->GlyphHeight());
    } else {
      font__->RenderGlyph(c, coordinate_system.Translate(render_point), alpha());
      render_point.x += font__->GlyphWidth(c);
    }
  }
}


#pragma mark - Private

GameSize Label::CalculateSize() {
  GameSize size = kGameSizeZero;
  for (int i = 0; i < text_.length(); i++) {
    char c = text_[i];
    if (c == '\n') {
      size.height += font__->GlyphHeight();
    } else {
      size.width += font__->GlyphWidth(c);
    }
  }
  size.height += font__->GlyphHeight();
  return size;
}
