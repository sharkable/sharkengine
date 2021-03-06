//
//  input_manager.cc
//  SharkEngine
//
//  Created by Jon Sharkey on 2014-01-05.
//  Copyright 2014 Sharkable. All rights reserved.
//

#include "sharkengine/input/input_manager.h"

#include "sharkengine/input/input_handler.h"

InputManager::InputManager() {
  memset(event_is_active_, 0, sizeof(bool) * InputEvent::kIdCount);
  pthread_mutex_init(&input_events_mutex_, NULL);
}

InputManager::~InputManager() {
  pthread_mutex_destroy(&input_events_mutex_);
}


void InputManager::AddEvent(const InputEvent &event) {
  shark_assert(!pthread_mutex_lock(&input_events_mutex_), "Error locking mutex.");
  input_events_.push_back(event);
  if (event.action() == InputEvent::kActionDown) {
    shark_assert(!event_is_active_[event.id()], "Active event restarted. Something went wrong.");
    event_is_active_[event.id()] = true;
  } else if (event.action() == InputEvent::kActionUp ||
      event.action() == InputEvent::kActionCancel) {
    shark_assert(event_is_active_[event.id()], "Event should be active. Something went wrong.");
    event_is_active_[event.id()] = false;
  }
  shark_assert(!pthread_mutex_unlock(&input_events_mutex_), "Error unlocking mutex.");
}

void InputManager::AddTouch(PlatformEventId platform_id, InputEvent::Action action,
                            GamePoint location) {
  if (action == InputEvent::kActionDown) {
#if DEBUG
    shark_assert(touch_ids_.find(platform_id) == touch_ids_.end(), "Touch used twice!");
#endif
    for (int id = InputEvent::kIdTouch0; id <= InputEvent::kIdTouch9; id++) {
      InputEvent::Id id_enum = static_cast<InputEvent::Id>(id);
      if (!event_is_active_[id]) {
        touch_ids_[platform_id] = id_enum;
        AddEvent(InputEvent(action, static_cast<InputEvent::Id>(id_enum), location));
        break;
      }
    }
  } else {
#if DEBUG
    shark_assert(touch_ids_.find(platform_id) != touch_ids_.end(), "Touch not found.");
#endif
    AddEvent(InputEvent(action, touch_ids_[platform_id], location));
    if (action == InputEvent::kActionUp || action == InputEvent::kActionCancel) {
      touch_ids_.erase(platform_id);
    }
  }
}

void InputManager::CancelAllActive() {
  shark_assert(!pthread_mutex_lock(&input_events_mutex_), "Error locking mutex.");
  for (int id = InputEvent::kIdNone; id < InputEvent::kIdCount; id++) {
    if (event_is_active_[id]) {
      input_events_.push_back(InputEvent(InputEvent::kActionCancel,
                                         static_cast<InputEvent::Id>(id)));
      event_is_active_[id] = false;
    }
  }
  touch_ids_.clear();
  shark_assert(!pthread_mutex_unlock(&input_events_mutex_), "Error unlocking mutex.");
}

void InputManager::HandleEvents(InputHandler &input_handler) {
  shark_assert(!pthread_mutex_lock(&input_events_mutex_), "Error locking mutex.");
  for (InputEvent event : input_events_) {
    input_handler.HandleInputEvent(event, CoordinateSystem::BaseSystem());
  }
  input_events_.clear();
  shark_assert(!pthread_mutex_unlock(&input_events_mutex_), "Error unlocking mutex.");
}
