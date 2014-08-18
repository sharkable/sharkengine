//
//  play_view.cc
//  Whack-a-Snake
//
//  Created by Jon Sharkey on 2014-08-17.
//  Copyright 2014 Sharkable. All rights reserved.
//

#include "whack-a-snake/play_view.h"

#include "sharkengine/shark_engine.h"
#include "sharkengine/sprite.h"

PlayView::PlayView(SharkEngine &shark_engine)
    : shark_engine_(shark_engine),
      ground_(Sprite(shark_engine, "ground"), kGamePointZero) {
  AddSnake(GamePoint(155, 355));
//  AddSnake(GamePoint(438, 359));
//  AddSnake(GamePoint(154, 620));
//  AddSnake(GamePoint(439, 620));
//  AddSnake(GamePoint(157, 898));
//  AddSnake(GamePoint(437, 896));
}


#pragma mark - Simulator

void PlayView::SimulateStep() {
  for (auto i : snakes_) {
    i->SimulateStep();
  }
}


#pragma mark - Renderer

void PlayView::Render(CoordinateSystem const &coordinate_system) {
  for (auto i : snakes_) {
    i->Render(coordinate_system);
  }
  ground_.Render(coordinate_system);
}


#pragma mark - InputHandler

bool PlayView::HandleInputEvent(InputEvent const &event,
                                CoordinateSystem const &coordinate_system) {
  for (auto i : snakes_) {
    if (i->HandleInputEvent(event, coordinate_system)) {
      return true;
    }
  }
  return false;
}


#pragma mark - Private

void PlayView::AddSnake(GamePoint position) {
  snakes_.push_back(sp<Snake>(new Snake(shark_engine_, position)));
}
