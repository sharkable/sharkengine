//
//  multi_select.h
//  SharkEngine
//
//  Created by Jon Sharkey on 2010-04-30.
//  Copyright 2010 Sharkable. All rights reserved.
//

#ifndef SHARKENGINE_ENTITIES_MULTISELECT_H_
#define SHARKENGINE_ENTITIES_MULTISELECT_H_

#include <vector>

#include "sharkengine/coordinates/coordinate_types.h"
#include "sharkengine/entities/animatable.h"
#include "sharkengine/input/input_handler.h"
#include "sharkengine/render/renderer.h"

class SharkEngine;
class Sprite;
class Touch;
namespace SharkSound {
  class Sound;
}

class MultiSelect : public Animatable, public Renderer, public InputHandler {
 public:
  MultiSelect(SharkEngine &shark_engine);
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
