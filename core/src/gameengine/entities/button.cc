//
//  button.m
//  GameEngine
//
//  Created by Jon Sharkey on 2010-04-30.
//  Copyright 2010 Sharkable. All rights reserved.
//

#include "gameengine/entities/button.h"

#include "gameengine/resource_loader.h"
#include "gameengine/touch.h"

#include "sharksound/sound.h"
#include "sharksound/sound_player.h"

using std::vector;

Button::Button(GameEngine *game_engine)
    : game_engine_(game_engine),
      state_(kButtonStateNormal) {
  Init();
}

Button::Button(GameEngine *game_engine, Sprite normal_sprite, Sprite pressed_sprite, GamePoint position)
    : Animatable(position),
      game_engine_(game_engine),
      normal_sprite_(normal_sprite),
      pressed_sprite_(pressed_sprite),
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


#pragma mark - ViewEntity

void Button::Render(GamePoint offset) {
  switch (state_) {
    case kButtonStateNormal: {
      normal_sprite_.Draw(position() + offset, angle(), alpha(), zoom());
      break;
    }
    case kButtonStatePressed: {
      pressed_sprite_.Draw(position() + offset, angle(), alpha(), zoom());
      break;
    }
  }
}

bool Button::TouchesBegan(GamePoint offset, vector<Touch> touches) {
  if (state_ == kButtonStateNormal) {
    for (int i = 0; i < touches.size(); i++) {
      if (ContainsPoint(touches[i].location() - offset)) {
        state_ = kButtonStatePressed;
        beep_sound_->Play();
        start_touch_ = touches[i].identifier();
        return true;
      }
    }
  } else if (state_ == kButtonStatePressed) {
    state_ = kButtonStateNormal;
  }
  return false;
}

void Button::TouchesEnded(GamePoint offset, vector<Touch> touches) {
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

#pragma mark - private

void Button::Init() {
  beep_sound_ = game_engine_->sound_player()->getSound("beep.wav");
}
