//
//  snake.h
//  Whack-a-Snake
//
//  Created by Jon Sharkey on 2014-08-17.
//  Copyright 2014 Sharkable. All rights reserved.
//

#ifndef WHACKASNAKE_SNAKE_H_
#define WHACKASNAKE_SNAKE_H_

#include "sharkengine/entities/simple_item.h"
#include "sharkengine/input/input_handler.h"
#include "sharkengine/render/renderer.h"
#include "sharkengine/simulation/simulator.h"

class SharkEngine;

class Snake : public SimpleItem, public InputHandler {
 public:
  typedef enum {
    kStateWaiting,
    kStatePopping,
    kStateShowing,
    kStateHiding,
    kStateDying
  } State;

  Snake(SharkEngine &shark_engine, GamePoint pop_up_center);

  // SimpleItem
  virtual void SimulateStep();
  virtual void Render(CoordinateSystem const &coordinate_system);

  // InputHandler
  virtual bool HandleInputEvent(InputEvent const &event, CoordinateSystem const &coordinate_system);

 private:
  static const GamePoint kBeginOffset;
  static const float kBeginAngle;
  static const GamePoint kEndOffset;
  static const float kEndAngle;

  void BeginWaiting();
  void BeginPopping();
  void BeginShowing();
  void BeginHiding();

  GamePoint pop_up_center_;
  State state_;
  int wait_ticks_;
};

#endif
