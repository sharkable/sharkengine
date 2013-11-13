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
  // This function is crazy. See bottom of page 22 of Sharkable Notes Vol 1.
  float angle_in_radians = angle * M_PI / 180.f;
  float cos_theta = cosf(angle_in_radians);
  float sin_theta = sinf(angle_in_radians);

  GamePoint render_center_point = rect_center(Rect());
  GamePoint render_point = position();
  GamePoint new_render_point;

  new_render_point.x = cos_theta * (render_point.x - render_center_point.x) -
      sin_theta * (render_point.y - render_center_point.y) + render_center_point.x;
  new_render_point.y = sin_theta * (render_point.x - render_center_point.x) +
      cos_theta * (render_point.y - render_center_point.y) + render_center_point.y;

  render_point = new_render_point + offset;

  for (int i = 0; i < text_.length(); i++) {
    char c = text_[i];
    if (c == '\n') {
      float glyph_height = font__->GlyphHeight();
      render_point = game_point_make(position().x + offset.x + sin_theta * glyph_height,
                                     render_point.y + cos_theta * glyph_height);
    } else {
      float glyph_width = font__->GlyphWidth(c);
      float glyph_height = font__->GlyphHeight();
      GamePoint glyph_center = render_point;
      glyph_center.x += glyph_width / 2;
      glyph_center.y += glyph_height / 2;

      GamePoint top_left;
      top_left.x = cos_theta * (render_point.x - glyph_center.x) -
          sin_theta * (render_point.y - glyph_center.y) + glyph_center.x;
      top_left.y = sin_theta * (render_point.x - glyph_center.x) +
          cos_theta * (render_point.y - glyph_center.y) + glyph_center.y;

      font__->RenderGlyph(c, render_point + render_point - top_left, alpha(), angle);
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
