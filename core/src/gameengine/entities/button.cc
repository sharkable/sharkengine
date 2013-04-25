//
//  button.m
//  GameEngine
//
//  Created by Jon Sharkey on 2010-04-30.
//  Copyright 2010 Sharkable. All rights reserved.
//

#include "gameengine/entities/button.h"

#include "gameengine/modules/sound_player.h"
#include "gameengine/resource_loader.h"
#include "gameengine/touch.h"

using std::vector;

Button::Button(Sprite normal_sprite, Sprite pressed_sprite, GamePoint position)
    : Animatable(position),
      normal_sprite_(normal_sprite),
      pressed_sprite_(pressed_sprite),
      state_(kButtonStateNormal),
      delegate_(NULL) {
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


// ViewEntity

void Button::Render() {
  switch (state_) {
    case kButtonStateNormal: {
      normal_sprite_.Draw(position(), angle(), alpha(), zoom());
      break;
    }
    case kButtonStatePressed: {
      pressed_sprite_.Draw(position(), angle(), alpha(), zoom());
      break;
    }
  }
}

bool Button::TouchesBegan(vector<Touch> touches) {
  if (state_ == kButtonStateNormal) {
    for (int i = 0; i < touches.size(); i++) {
      if (ContainsPoint(touches[i].location())) {
        state_ = kButtonStatePressed;
        SoundPlayer::instance()->playSound(kSoundButton);
        start_touch_ = touches[i].identifier();
        return true;
      }
    }
  } else if (state_ == kButtonStatePressed) {
    state_ = kButtonStateNormal;
  }
  return false;
}

void Button::TouchesEnded(vector<Touch> touches) {
  if (state_ == kButtonStatePressed) {
    for (int i = 0; i < touches.size(); i++) {
      if (touches[i].identifier() == start_touch_) {
        state_ = kButtonStateNormal;
        if (delegate_) {
          delegate_->ButtonPressed(this);
        }
        break;
      }
    }
  }
}
