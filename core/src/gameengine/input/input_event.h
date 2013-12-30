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

typedef enum {
  kInputActionDown,
  kInputActionMove,
  kInputActionUp,
  kInputActionCancelAll
} InputAction;

typedef enum {
  kInputIdTouch0,
  kInputIdTouch1,
  kInputIdTouch2,
  kInputIdTouch3,
  kInputIdTouch4,
  kInputIdTouch5,
  kInputIdTouch6,
  kInputIdTouch7,
  kInputIdTouch8,
  kInputIdTouch9,
  kInputIdMouse,
  kInputIdMouseButton0,
  kInputIdKeyboardSpace,
  kInputIdKeyboardEsc,
  kInputIdKeyboardOther,
  kInputIdCancelAll
} InputId;

class InputEvent {
 public:
  InputEvent(InputAction action, InputId id, GamePoint location = kGamePointZero);

  InputAction Action() const;
  InputId Id() const;
  GamePoint Location() const;

  bool IsMouse() const;
  bool IsKey() const;
  bool IsTouch() const;
  bool HasLocation() const;

 private:
  InputAction action_;
  InputId id_;
  GamePoint location_;
};

#endif
