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


#pragma mark - ViewEntity

void Label::Render(GamePoint offset) {
  GamePoint render_point = position() + offset;
  for (int i = 0; i < text_.length(); i++) {
    char c = text_[i];
    if (c == '\n') {
      render_point = game_point_make(position().x + offset.x,
                                     render_point.y + font__->GlyphHeight());
    } else {
      font__->RenderGlyph(c, render_point, alpha());
      render_point.x += font__->GlyphWidth(c);
    }
  }
}

void Label::Render(GamePoint offset, float angle) {
  float angle_in_radians = angle * M_PI / 180.f;
  float cos_theta = cosf(angle_in_radians);
  float sin_theta = sinf(angle_in_radians);

  GamePoint render_center_point = rect_center(Rect()) + offset;
  GamePoint render_point = position() + offset;
  GamePoint new_render_point;

  new_render_point.x = cos_theta * (render_point.x - render_center_point.x) -
      sin_theta * (render_point.y - render_center_point.y) + render_center_point.x;
  new_render_point.y = sin_theta * (render_point.x - render_center_point.x) +
      cos_theta * (render_point.y - render_center_point.y) + render_center_point.y;
  render_point = new_render_point;

  for (int i = 0; i < text_.length(); i++) {
    char c = text_[i];
    if (c == '\n') {
      float glyph_height = font__->GlyphHeight();
      render_point = game_point_make(position().x + offset.x + sin_theta * glyph_height,
                                     render_point.y + cos_theta * glyph_height);
    } else {
      font__->RenderGlyph(c, render_point, alpha(), angle);
      float glyph_width = font__->GlyphWidth(c);
      render_point.x += cos_theta * glyph_width;
      render_point.y += sin_theta * glyph_width;
    }
  }
}

GameRect Label::Rect() {
  return game_rect_make(position(), size_);
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
  shark_log("size is: %f, %f", size.width, size.height);
  return size;
}
