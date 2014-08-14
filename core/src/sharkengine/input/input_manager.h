//
//  input_manager.h
//  SharkEngine
//
//  Created by Jon Sharkey on 2014-01-05.
//  Copyright 2014 Sharkable. All rights reserved.
//

#ifndef SHARKENGINE_INPUT_INPUTMANAGER_H_
#define SHARKENGINE_INPUT_INPUTMANAGER_H_

#include <utility>
#include <map>
#include <vector>

#include "sharkengine/input/input_event.h"

class InputHandler;

class InputManager {
 public:
  typedef unsigned long PlatformEventId;
  
  InputManager();
  ~InputManager();

  void AddEvent(const InputEvent &event);
  void AddTouch(PlatformEventId platform_id, InputEvent::Action action, GamePoint location);
  void CancelAllActive();
  void HandleEvents(InputHandler &input_handler);

 private:
  std::vector<InputEvent> input_events_;
  bool event_is_active_[InputEvent::kIdCount];
  std::map<PlatformEventId, InputEvent::Id> touch_ids_;
  pthread_mutex_t input_events_mutex_;
};

#endif
