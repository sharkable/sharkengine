//
//  font.h
//  SharkEngine
//
//  Created by Jon Sharkey on 2013-10-18.
//  Copyright 2013 Sharkable. All rights reserved.
//

#ifndef SHARKENGINE_FONT_H_
#define SHARKENGINE_FONT_H_

#include <map>
#include <string>

#include "sharkengine/coordinates/coordinate_system.h"
#include "sharkengine/coordinates/coordinate_types.h"
#include "sharkengine/opengl/texture2d.h"

class SharkEngine;

class Font {
 public:
  Font(SharkEngine &shark_engine, std::string font_name);
  void RenderGlyph(char glyph, CoordinateSystem const &coordinate_system, float alpha = 1.f);
  float GlyphWidth(char glyph);
  float GlyphHeight();

 private:
  std::string TextureNameForCharacter(char c);

  SharkEngine &shark_engine_;
  std::string font_name_;
  std::map<char, Texture2D> glyphs_;
};

#endif
