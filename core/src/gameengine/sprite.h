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

class Sprite {
 public:
  typedef enum {
    kAnchorTopLeft,
    kAnchorCenter,
  } Anchor;

  Sprite(GameEngine &game_engine, Anchor anchor = kAnchorTopLeft)
    : game_engine_(game_engine),
      anchor_(anchor) {
  }

  Sprite(GameEngine &game_engine, Texture2D texture, Anchor anchor = kAnchorTopLeft)
    : game_engine_(game_engine),
      anchor_(anchor),
      texture_(texture) {
  }

  Sprite(GameEngine &game_engine, std::string texture_name, Anchor anchor = kAnchorTopLeft)
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

  Anchor anchor() { return anchor_; }
  void set_anchor(Anchor anchor) { anchor_ = anchor; }

  GameSize content_size() {
    return game_engine_.screen_size_to_game_size(texture_.content_size());
  }

  void Draw(CoordinateSystem coordinate_system) {
    texture_.DrawAtPoint(game_engine_.game_point_to_screen_point(coordinate_system.origin()),
                         1.f, 1.f, coordinate_system.angle(), anchor_ == kAnchorCenter);
 } 

  void DrawAtPoint(GamePoint position) {
    texture_.DrawAtPoint(game_engine_.game_point_to_screen_point(position), 1.f, 1.f, 0.f,
                         anchor_ == kAnchorCenter);
  }

  void DrawAtPointAngle(GamePoint position, GLfloat angle) {
    texture_.DrawAtPoint(game_engine_.game_point_to_screen_point(position), 1.f, 1.f, angle,
                         anchor_ == kAnchorCenter);
  }

  void Draw(GamePoint position, GLfloat angle, GLfloat alpha, GLfloat zoom) {
    texture_.DrawAtPoint(game_engine_.game_point_to_screen_point(position), alpha, zoom, angle,
                         anchor_ == kAnchorCenter);
  }


  GameEngine &game_engine_;
  Anchor anchor_;
  Texture2D texture_;
};

#endif
