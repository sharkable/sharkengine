//
//  font.h
//  GameEngine
//
//  Created by Jon Sharkey on 2013-10-18.
//  Copyright 2013 Sharkable. All rights reserved.
//

#ifndef GAMEENGINE_FONT_H_
#define GAMEENGINE_FONT_H_

#include <map>
#include <string>

#include "gameengine/coordinates/coordinate_types.h"
#include "gameengine/opengl/texture2d.h"

class GameEngine;

class Font {
 public:
  Font(GameEngine &game_engine, std::string font_name);
  void RenderGlyph(char glyph, GamePoint position, float alpha = 1.f, float angle = 0.f);
  float GlyphWidth(char glyph);
  float GlyphHeight();

 private:
  std::string TextureNameForCharacter(char c);

  GameEngine &game_engine_;
  std::string font_name_;
  std::map<char, Texture2D> glyphs_;
};

#endif
