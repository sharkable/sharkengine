//
//  snake.cc
//  Whack-a-Snake
//
//  Created by Jon Sharkey on 2014-08-17.
//  Copyright 2014 Sharkable. All rights reserved.
//

#include "whack-a-snake/snake.h"

#include <cstdlib>

Snake::Snake(SharkEngine &shark_engine, GamePoint pop_up_center)
    : SimpleItem(Sprite(shark_engine, "snake", Sprite::kAnchorCenter), kGamePointZero),
      pop_up_center_(pop_up_center),
      state_(kStateWaiting),
      wait_ticks_(0) {
  BeginWaiting();
}


#pragma mark - Simulator

void Snake::SimulateStep() {
  SimpleItem::SimulateStep();

  if (wait_ticks_-- == 0) {
    switch (state_) {
      case kStateWaiting:
        BeginPopping();
        break;
      case kStatePopping:
        BeginShowing();
        break;
      case kStateShowing:
        BeginHiding();
        break;
      case kStateHiding:
        BeginWaiting();
        break;
      case kStateDying:
        break;
    }
  }
}


#pragma mark -  SimpleItem

void Snake::Render(CoordinateSystem const &coordinate_system) {
  SimpleItem::Render(coordinate_system.Translate(pop_up_center_));
}

bool Snake::HandleInputEvent(InputEvent const &event, CoordinateSystem const &coordinate_system) {
  if (event.action() == InputEvent::kActionDown && event.HasLocation()) {
    GamePoint point = coordinate_system.Translate(event.location() - pop_up_center_).origin();
    shark_log("point: %s", to_string(event.location()).c_str());
    if (point.x * point.x + point.y * point.y < 20) {
      return true;
    }
  }
  return false;
}


#pragma mark - private

const GamePoint Snake::kBeginOffset(-105, 105);
const float Snake::kBeginAngle(-45);
const GamePoint Snake::kEndOffset(0, 15);
const float Snake::kEndAngle(0);

void Snake::BeginWaiting() {
  state_ = kStateWaiting;
  wait_ticks_ = rand() % 120;

  set_position(kBeginOffset);
  set_angle(kBeginAngle);
}

void Snake::BeginPopping() {
  state_ = kStatePopping;
  wait_ticks_ = 60;

  AnimateToPosition(kEndOffset, kAnimationTypeCubicEaseInOut, 60);
  AnimateToAngle(kEndAngle, kAnimationTypeCubicEaseInOut, 60);
}

void Snake::BeginShowing() {
  state_ = kStateShowing;
  wait_ticks_ = 30 + rand() % 60;

}

void Snake::BeginHiding() {
  state_ = kStateHiding;
  wait_ticks_ = 60;

  AnimateToPosition(kBeginOffset, kAnimationTypeCubicEaseInOut, 60);
  AnimateToAngle(kBeginAngle, kAnimationTypeCubicEaseInOut, 60);
}
