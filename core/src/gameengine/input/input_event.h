//
//  input_event.h
//  GameEngine
//
//  Created by Jon Sharkey on 2013-12-19.
//  Copyright 2013 Sharkable. All rights reserved.
//

#ifndef GAMEENGINE_INPUT_INPUTEVENT_H_
#define GAMEENGINE_INPUT_INPUTEVENT_H_

#include "gameengine/coordinates/coordinate_types.h"

class InputEvent {
 public:
  typedef enum {
    kActionDown,
    kActionMove,
    kActionUp,
    kActionCancelAll
  } Action;

  typedef enum {
    kIdTouch0,
    kIdTouch1,
    kIdTouch2,
    kIdTouch3,
    kIdTouch4,
    kIdTouch5,
    kIdTouch6,
    kIdTouch7,
    kIdTouch8,
    kIdTouch9,
    kIdMouse,
    kIdMouseButton0,
    kIdKeyboardSpace,
    kIdKeyboardEsc,
    kIdKeyboardOther,
    kIdCancelAll
  } Id;

  InputEvent(Action action, Id id, GamePoint location = kGamePointZero);

  Action action() const;
  Id id() const;
  GamePoint location() const;

  bool IsMouse() const;
  bool IsKey() const;
  bool IsTouch() const;
  bool HasLocation() const;

 private:
  Action action_;
  Id id_;
  GamePoint location_;
};

#endif