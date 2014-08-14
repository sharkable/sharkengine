//
//  multi_select.h
//  SharkEngine
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
#include "gameengine/render/renderer.h"

class GameEngine;
class Sprite;
class Touch;
namespace SharkSound {
  class Sound;
}

class MultiSelect : public Animatable, public Renderer, public InputHandler {
 public:
  MultiSelect(GameEngine &game_engine);
  ~MultiSelect();

  void Add(Sprite normal_sprite, Sprite selected_sprite, GamePoint position);

  // Renderer
  virtual void Render(CoordinateSystem const &coordinate_system);

  // InputHandler
  virtual bool HandleInputEvent(InputEvent const &event, CoordinateSystem const &coordinate_system);

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
