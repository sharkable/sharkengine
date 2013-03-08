//
//  sprite.h
//  GameEngine
//
//  Created by Jon Sharkey on 2013-01-27.
//  Copyright 2013 Sharkable. All rights reserved.
//

#ifndef GAMEENGINE_SPRITE_H_
#define GAMEENGINE_SPRITE_H_

#include "opengl/texture2D.h"

#include "gameengine/game_engine.h"
#include "gameengine/resource_loader.h"

class Sprite {
 public:
  Sprite() { }

  Sprite(sp<GameEngine> game_engine) : game_engine_(game_engine) { }

  Sprite(sp<GameEngine> game_engine, Texture2D texture)
    : game_engine_(game_engine),
      texture_(texture) {
  }

  Sprite(sp<GameEngine> game_engine, std::string texture_name) : game_engine_(game_engine) {
    texture_ = ResourceLoader::Instance().TextureWithName(texture_name);
  }

  // TODO consider removing this.
  Texture2D texture() { return texture_; }

  void set_texture(Texture2D texture) { texture_ = texture; }

  GameSize content_size() {
    return game_engine_->screen_size_to_game_size(texture_.content_size());
  }

  void DrawAtPoint(GamePoint position) {
    texture_.DrawAtPoint(game_engine_->game_point_to_screen_point(position));
  }

  void DrawAtPointAngle(GamePoint position, GLfloat angle) {
    texture_.DrawAtPointAngle(game_engine_->game_point_to_screen_point(position), angle);
  }

  void Draw(GamePoint position, GLfloat angle, GLfloat alpha, GLfloat zoom) {
    texture_.DrawAtPoint(game_engine_->game_point_to_screen_point(position), alpha, zoom, angle, 0);
  }

  void DrawAtPointLeftRatio(GamePoint position, GLfloat left_ratio) {
    texture_.DrawAtPointLeftRatio(game_engine_->game_point_to_screen_point(position), left_ratio);
  }

  void DrawAtPointRightRatio(GamePoint position, GLfloat right_ratio) {
    texture_.DrawAtPointRightRatio(game_engine_->game_point_to_screen_point(position), right_ratio);
  }

 private:
  sp<GameEngine> game_engine_;
  Texture2D texture_;
};

#endif
