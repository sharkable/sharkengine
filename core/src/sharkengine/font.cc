//
//  font.cc
//  SharkEngine
//
//  Created by Jon Sharkey on 2013-10-18.
//  Copyright 2013 Sharkable. All rights reserved.
//

#include "sharkengine/font.h"

#include "sharkengine/resource_loader.h"
#include "sharkengine/shark_engine.h"

Font::Font(SharkEngine &shark_engine, std::string font_name)
    : shark_engine_(shark_engine),
      font_name_(font_name) {
  char const * const characters =
      "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ.!?,:;%\"+-/";
  size_t num_characters = strlen(characters);
  for (int i = 0; i < num_characters; i++) {
    char c = characters[i];
    glyphs_[c] = shark_engine.resource_loader().TextureWithName(TextureNameForCharacter(c));
  }
}

void Font::RenderGlyph(char glyph, CoordinateSystem const &coordinate_system, float alpha) {
  if (glyph == ' ') {
    return;
  }
#if DEBUG
  shark_assert(glyphs_[glyph].data_loaded(), "Cannot draw character: %c %d", glyph, glyph);
#endif

  glyphs_[glyph].Draw(shark_engine_.game_point_to_screen_point(coordinate_system.origin()), alpha,
                      coordinate_system.scale(), coordinate_system.angle(), false);
}

float Font::GlyphWidth(char glyph) {
  if (glyph == ' ') {
    return 15;
  }
  return glyphs_[glyph].content_size().width - 3;  // TODO HACK
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
  if (c == '/') {
    return font_name_ + "_divide";
  }
  return font_name_ + "_" + c;
}
