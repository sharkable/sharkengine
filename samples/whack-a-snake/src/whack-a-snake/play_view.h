//
//  play_view.h
//  Whack-a-Snake
//
//  Created by Jon Sharkey on 2014-08-17.
//  Copyright 2014 Sharkable. All rights reserved.
//

#ifndef WHACKASNAKE_PLAYVIEW_H_
#define WHACKASNAKE_PLAYVIEW_H_

#include "whack-a-snake/snake.h"

#include <vector>

#include "sharkengine/entities/simple_item.h"
#include "sharkengine/input/input_handler.h"
#include "sharkengine/render/renderer.h"
#include "sharkengine/simulation/simulator.h"

class SharkEngine;

class PlayView : public Simulator, public Renderer, public InputHandler {
 public:
  PlayView(SharkEngine &shark_engine);

  // Simulator
  virtual void SimulateStep();

  // Renderer
  virtual void Render(CoordinateSystem const &coordinate_system);

  // InputHandler
  virtual bool HandleInputEvent(InputEvent const &event, CoordinateSystem const &coordinate_system);

 private:
  void AddSnake(GamePoint position);

  SharkEngine &shark_engine_;
  SimpleItem ground_;
  std::vector<sp<Snake>> snakes_;
};

#endif
