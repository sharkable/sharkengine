//
//  button.m
//  AirHockey
//
//  Created by Jonathan Sharkey on 10-04-30.
//  Copyright 2010 Sharkable. All rights reserved.
//

#include "gameengine/entities/button.h"

#include "gameengine/resource_loader.h"
#include "gameengine/touch.h"
#include "soundengine/sound_player.h"

Button::Button(Sprite normal_sprite, Sprite pressed_sprite, GamePoint position)
    : Animatable(position),
      normal_sprite_(normal_sprite),
      pressed_sprite_(pressed_sprite),
      state_(kButtonStateNormal),
      delegate_(NULL) {
}

Button::~Button() {
  if (normal_sprite_.texture().loaded()) {
    ResourceLoader::Instance().ReleaseResource(normal_sprite_.texture());
  }
  if (pressed_sprite_.texture().loaded()) {
    ResourceLoader::Instance().ReleaseResource(pressed_sprite_.texture());
  }
}

bool Button::ContainsPoint(GamePoint p) {
  // TODO: THIS IS A HACK
  // For this big release, I zoom one button: the story stuff.
  if (zoom() > 1) {
    return true;
  }
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

void Button::TouchesBegan(vector<Touch> touches) {
  if (state_ == kButtonStateNormal) {
    for (int i = 0; i < touches.size(); i++) {
      if (ContainsPoint(touches[i].location())) {
        state_ = kButtonStatePressed;
        SoundPlayer::instance()->playSound(kSoundButton);
      }
    }
  }
}

void Button::TouchesEnded(vector<Touch> touches) {
  if (state_ == kButtonStatePressed) {
    state_ = kButtonStateNormal;
    for (int i = 0; i < touches.size(); i++) {
      if (ContainsPoint(touches[i].location())) {
        if (delegate_) {
          delegate_->ButtonPressed(this);
        }
      }
    }
  }
}
