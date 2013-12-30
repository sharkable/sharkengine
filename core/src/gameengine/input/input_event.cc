//
//  input_event.cc
//  GameEngine
//
//  Created by Jon Sharkey on 2013-12-19.
//  Copyright 2013 Sharkable. All rights reserved.
//

#include "gameengine/input/input_event.h"

InputEvent::InputEvent(InputAction action, InputId id, GamePoint location)
    : action_(action),
      id_(id),
      location_(location) {
#if DEBUG
  if (IsKey()) shark_assert(location == kGamePointZero, "Keys don't have locations.");
  if (action == kInputActionCancelAll) {
    shark_assert(id == kInputIdCancelAll, "CancelAll action needs CancelAll id.");
  }
#endif
}

InputAction InputEvent::Action() const {
  return action_;
}

InputId InputEvent::Id() const {
  return id_;
}

GamePoint InputEvent::Location() const {
  shark_assert(HasLocation(), "No location for InputEvent.");
  return location_;
}

bool InputEvent::IsMouse() const {
  return id_ == kInputIdMouse;
}

bool InputEvent::IsKey() const {
  return id_ >= kInputIdKeyboardSpace && id_ < kInputIdCancelAll;
}

bool InputEvent::IsTouch() const {
  return id_ < kInputIdTouch9;
}

bool InputEvent::HasLocation() const {
  return id_ <= kInputIdMouseButton0;
}
