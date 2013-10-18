//
//  font.cc
//  Pigeon
//
//  Created by Jon Sharkey on 2013-10-18.
//  Copyright 2013 Sharkable. All rights reserved.
//

#include "gameengine/font.h"

#include "gameengine/game_engine.h"
#include "gameengine/resource_loader.h"

Font::Font(GameEngine *game_engine, std::string font_name)
    : game_engine_(game_engine),
      font_name_(font_name) {
  char const * const characters =
      "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ.!?,:;%\"";
  size_t num_characters = strlen(characters);
  for (int i = 0; i < num_characters; i++) {
    char c = characters[i];
    glyphs_[c] = game_engine->resource_loader().TextureWithName(TextureNameForCharacter(c));
  }
}

void Font::RenderGlyph(char glyph, GamePoint position) {
  if (glyph == ' ') {
    return;
  }
  glyphs_[glyph].DrawAtPoint(game_engine_->game_point_to_screen_point(position));
}

float Font::GlyphWidth(char glyph) {
  if (glyph == ' ') {
    return 15;
  }
  return glyphs_[glyph].content_size().width;
}

float Font::GlyphHeight() {
  return glyphs_['A'].content_size().height;
}


#pragma mark - private

std::string Font::TextureNameForCharacter(char c) {
  if (c >= 'A' && c <= 'Z') {
    return font_name_ + "_" + c + "_big";
  }
  if (c == '.') {
    return font_name_ + "_dot";
  }
  if (c == '!') {
    return font_name_ + "_exclamation";
  }
  if (c == '?') {
    return font_name_ + "_question";
  }
  if (c == ',') {
    return font_name_ + "_comma";
  }
  if (c == ':') {
    return font_name_ + "_colon";
  }
  if (c == ';') {
    return font_name_ + "_semicolon";
  }
  if (c == '%') {
    return font_name_ + "_percent";
  }
  if (c == '"') {
    return font_name_ + "_quote";
  }
  return font_name_ + "_" + c;
}
