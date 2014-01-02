//
//  button.m
//  GameEngine
//
//  Created by Jon Sharkey on 2010-04-30.
//  Copyright 2010 Sharkable. All rights reserved.
//

#include "gameengine/entities/button.h"

#include "sharksound/sound.h"
#include "sharksound/sound_controller.h"

#include "gameengine/resource_loader.h"

using std::vector;

Button::Button(GameEngine &game_engine)
    : Animatable(),
      game_engine_(game_engine),
      normal_sprite_(game_engine),
      pressed_sprite_(game_engine),
      pressed_offset_(kGamePointZero),
      state_(kButtonStateNormal) {
  Init();
}

Button::Button(GameEngine &game_engine, Sprite normal_sprite, Sprite pressed_sprite,
               GamePoint position)
    : Animatable(position),
      game_engine_(game_engine),
      normal_sprite_(normal_sprite),
      pressed_sprite_(pressed_sprite),
      pressed_offset_(kGamePointZero),
      state_(kButtonStateNormal),
      delegate_(NULL) {
  Init();
}

Button::~Button() {
  if (normal_sprite_.texture().loaded()) {
    // TODO game_engine->resource_loader().ReleaseResource(normal_sprite_.texture());
  }
  if (pressed_sprite_.texture().loaded()) {
    // TODO ResourceLoader::Instance().ReleaseResource(pressed_sprite_.texture());
  }
}

bool Button::ContainsPoint(GamePoint p) {
  return p.x >= position().x &&
      p.y >= position().y &&
      p.x < position().x + pressed_sprite_.content_size().width &&
      p.y < position().y + pressed_sprite_.content_size().height;
}


#pragma mark - Renderer

void Button::Render(CoordinateSystem const &coordinate_system) {
  switch (state_) {
    case kButtonStateNormal: {
      normal_sprite_.Draw(position() + pressed_offset_ + coordinate_system.origin(),
                          angle() + coordinate_system.angle(), alpha(), scale());
      break;
    }
    case kButtonStatePressed: {
      pressed_sprite_.Draw(position() + pressed_offset_ + coordinate_system.origin(),
                           angle() + coordinate_system.angle(), alpha(), scale());
      break;
    }
  }
}


#pragma mark - InputHandler

bool Button::HandleInputEvent(InputEvent const &event) {
  if (event.action() == InputEvent::kActionDown && event.HasLocation()) {
    if (state_ == kButtonStateNormal) {
      if (ContainsPoint(event.location())) {
        state_ = kButtonStatePressed;
        beep_sound_->Play();
        start_touch_ = event.id();
        if (delegate_) {
          delegate_->ButtonDown(this);
        }
        return true;
      }
    }
  } else if (event.action() == InputEvent::kActionUp && event.HasLocation()) {
    if (state_ == kButtonStatePressed && event.id() == start_touch_) {
      state_ = kButtonStateNormal;
      if (delegate_) {
        delegate_->ButtonUp(this);
      }
      return true;
    }
  }
  return false;
}


#pragma mark - private

void Button::Init() {
  beep_sound_ = game_engine_.sound()->GetSound("sounds/beep.wav");
}
