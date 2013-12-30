//
//  multi_select.h
//  GameEngine
//
//  Created by Jon Sharkey on 2010-04-30.
//  Copyright 2010 Sharkable. All rights reserved.
//

#ifndef GAMEENGINE_ENTITIES_MULTISELECT_H_
#define GAMEENGINE_ENTITIES_MULTISELECT_H_

#include <vector>

#include "gameengine/coordinates/coordinate_types.h"
#include "gameengine/entities/animatable.h"
#include "gameengine/input/input_handler.h"

class GameEngine;
class Sprite;
class Touch;
namespace SharkSound {
  class Sound;
}

class MultiSelect : public Animatable, public InputHandler {
 public:
  MultiSelect(GameEngine &game_engine);
  ~MultiSelect();

  void Add(Sprite normal_sprite, Sprite selected_sprite, GamePoint position);

  // ViewEntity
  virtual void Render(GamePoint offset);

  // InputHandler
  virtual bool HandleInputEvent(InputEvent const &event);

  // Accessors
  int selected_value() { return selected_value_; };
  void set_selected_value(int selected_value) { selected_value_ = selected_value; }

 private:
  std::vector<Sprite> normal_sprites_;
  std::vector<Sprite> selected_sprites_;
  std::vector<double> positions_x_;
  std::vector<double> positions_y_;
  SharkSound::Sound *click_sound_;
  int selected_value_;
};

#endif
