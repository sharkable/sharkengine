//
//  sprite.h
//  SharkEngine
//
//  Created by Jon Sharkey on 2013-01-27.
//  Copyright 2013 Sharkable. All rights reserved.
//

#ifndef SHARKENGINE_SPRITE_H_
#define SHARKENGINE_SPRITE_H_

#include "sharkengine/resource_loader.h"
#include "sharkengine/shark_engine.h"
#include "sharkengine/coordinates/coordinate_system.h"
#include "sharkengine/opengl/texture2d.h"

class Sprite {
 public:
  typedef enum {
    kAnchorTopLeft,
    kAnchorCenter,
  } Anchor;

  Sprite(SharkEngine &shark_engine, Anchor anchor = kAnchorTopLeft)
    : shark_engine_(shark_engine),
      anchor_(anchor),
      alpha_(1.f) {
  }

  Sprite(SharkEngine &shark_engine, Texture2D texture, Anchor anchor = kAnchorTopLeft)
    : shark_engine_(shark_engine),
      anchor_(anchor),
      texture_(texture),
      alpha_(1.f) {
  }

  Sprite(SharkEngine &shark_engine, std::string texture_name, Anchor anchor = kAnchorTopLeft)
    : shark_engine_(shark_engine),
      anchor_(anchor),
      alpha_(1.f) {
    texture_ = shark_engine.resource_loader().TextureWithName(texture_name);
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
  void set_alpha(float alpha) { alpha_ = alpha; }

  GameSize content_size() {
    return shark_engine_.screen_size_to_game_size(texture_.content_size());
  }

  void Draw(CoordinateSystem coordinate_system) {
    texture_.Draw(shark_engine_.game_point_to_screen_point(coordinate_system.origin()),
                  alpha_, coordinate_system.scale(), coordinate_system.angle(),
                  anchor_ == kAnchorCenter);
  }

  void Draw(CoordinateSystem coordinate_system, GameRect subtexture) {
    texture_.Draw(shark_engine_.game_point_to_screen_point(coordinate_system.origin()), subtexture,
                  alpha_, coordinate_system.scale(), coordinate_system.angle(),
                  anchor_ == kAnchorCenter);
  }

  SharkEngine &shark_engine_;
  Anchor anchor_;
  Texture2D texture_;
  float alpha_;
};

#endif
