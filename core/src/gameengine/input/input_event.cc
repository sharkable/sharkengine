//
//  input_event.cc
//  GameEngine
//
//  Created by Jon Sharkey on 2013-12-19.
//  Copyright 2013 Sharkable. All rights reserved.
//

#include "gameengine/input/input_event.h"

InputEvent::InputEvent(Action action, Id id, GamePoint location)
    : action_(action),
      id_(id),
      location_(location) {
#if DEBUG
  if (IsKey()) shark_assert(location == kGamePointZero, "Keys don't have locations.");
  if (action == kActionCancelAll) {
    shark_assert(id == kIdCancelAll, "CancelAll action needs CancelAll id.");
  }
#endif
}

InputEvent::Action InputEvent::action() const {
  return action_;
}

InputEvent::Id InputEvent::id() const {
  return id_;
}

GamePoint InputEvent::location() const {
  shark_assert(HasLocation(), "No location for InputEvent.");
  return location_;
}

bool InputEvent::IsMouse() const {
  return id_ == kIdMouse;
}

bool InputEvent::IsKey() const {
  return id_ >= kIdKeyboardSpace && id_ < kIdCancelAll;
}

bool InputEvent::IsTouch() const {
  return id_ < kIdTouch9;
}

bool InputEvent::HasLocation() const {
  return id_ <= kIdMouseButton0;
}
