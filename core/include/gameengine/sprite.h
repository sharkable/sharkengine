//
//  sprite.h
//  GameEngine
//
//  Created by Jon Sharkey on 2013-01-27.
//  Copyright 2013 Sharkable. All rights reserved.
//

#ifndef GAMEENGINE_SPRITE_H_
#define GAMEENGINE_SPRITE_H_

#include "gameengine/game_engine.h"
#include "gameengine/resource_loader.h"
#include "gameengine/coordinates/coordinate_system.h"
#include "gameengine/opengl/texture2d.h"

typedef enum {
  kSpriteAnchorTopLeft,
  kSpriteAnchorCenter,
} SpriteAnchor;

class Sprite {
 public:
  Sprite(GameEngine &game_engine, SpriteAnchor anchor = kSpriteAnchorTopLeft)
    : game_engine_(game_engine),
      anchor_(anchor) {
  }

  Sprite(GameEngine &game_engine, Texture2D texture, SpriteAnchor anchor = kSpriteAnchorTopLeft)
    : game_engine_(game_engine),
      anchor_(anchor),
      texture_(texture) {
  }

  Sprite(GameEngine &game_engine, std::string texture_name,
         SpriteAnchor anchor = kSpriteAnchorTopLeft)
    : game_engine_(game_engine),
      anchor_(anchor) {
    texture_ = game_engine.resource_loader().TextureWithName(texture_name);
  }

  Sprite & operator=(Sprite const &sprite) {
    anchor_ = sprite.anchor_;
    texture_ = sprite.texture_;
    return *this;
  }

  // TODO consider removing this.
  Texture2D texture() { return texture_; }
  void set_texture(Texture2D texture) { texture_ = texture; }

  SpriteAnchor anchor() { return anchor_; }
  void set_anchor(SpriteAnchor anchor) { anchor_ = anchor; }

  GameSize content_size() {
    return game_engine_.screen_size_to_game_size(texture_.content_size());
  }

  void Draw(CoordinateSystem coordinate_system) {
    texture_.DrawAtPointAngle(anchor_point_to_screen_point(coordinate_system.origin(), 1.f),
                              coordinate_system.angle());
  }

  void DrawAtPoint(GamePoint position) {
    texture_.DrawAtPoint(anchor_point_to_screen_point(position, 1.f));
  }

  void DrawAtPointAngle(GamePoint position, GLfloat angle) {
    texture_.DrawAtPointAngle(anchor_point_to_screen_point(position, 1.f), angle);
  }

  void Draw(GamePoint position, GLfloat angle, GLfloat alpha, GLfloat zoom) {
    texture_.DrawAtPoint(anchor_point_to_screen_point(position, zoom), alpha, zoom, angle, 0);
  }

  void DrawAtPointLeftRatio(GamePoint position, GLfloat left_ratio) {
    texture_.DrawAtPointLeftRatio(anchor_point_to_screen_point(position, 1.f), left_ratio);
  }

  void DrawAtPointRightRatio(GamePoint position, GLfloat right_ratio) {
    texture_.DrawAtPointRightRatio(anchor_point_to_screen_point(position, 1.f), right_ratio);
  }

 private:
  ScreenPoint anchor_point_to_screen_point(GamePoint point, GLfloat zoom) {
    switch (anchor_) {
      case kSpriteAnchorTopLeft:
        return game_engine_.game_point_to_screen_point(point);
      case kSpriteAnchorCenter:
        GameSize size = content_size();
        point.x -= size.width / 2.f;
        point.y -= size.height / 2.f;
        return game_engine_.game_point_to_screen_point(point);
    }
  }

  GameEngine &game_engine_;
  SpriteAnchor anchor_;
  Texture2D texture_;
};

#endif
