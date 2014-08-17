//
//  multi_select.cc
//  SharkEngine
//
//  Created by Jon Sharkey on 2010-04-30.
//  Copyright 2010 Sharkable. All rights reserved.
//

#include "sharkengine/entities/multi_select.h"

#include "sharksound/sound.h"
#include "sharksound/sound_controller.h"

#include "sharkengine/resource_loader.h"
#include "sharkengine/shark_engine.h"
#include "sharkengine/sprite.h"

using std::vector;

MultiSelect::MultiSelect(GameEngine &game_engine)
    : Animatable(),
      selected_value_(0) {
  click_sound_ = game_engine.sound()->GetSound("sounds/button_click.wav");
}

MultiSelect::~MultiSelect() {
  for (int i = 0; i < normal_sprites_.size(); i++) {
    // TODO ResourceLoader::Instance().ReleaseResource(normal_sprites_[i].texture());
  }
  for (int i = 0; i < selected_sprites_.size(); i++) {
    // TODO ResourceLoader::Instance().ReleaseResource(selected_sprites_[i].texture());
  }
}

void MultiSelect::Add(Sprite normal_sprite, Sprite selected_sprite, GamePoint position) {
  normal_sprites_.push_back(normal_sprite);
  selected_sprites_.push_back(selected_sprite);
  positions_x_.push_back(position.x);
  positions_y_.push_back(position.y);
}


#pragma mark - Renderer

void MultiSelect::Render(CoordinateSystem const &coordinate_system) {
  for (int i = 0; i < normal_sprites_.size(); i++) {
    GamePoint p(positions_x_[i], positions_y_[i]);
    if (i == selected_value_) {
      selected_sprites_[i].set_alpha(alpha());
      selected_sprites_[i].Draw(coordinate_system.Translate(p));
    } else {
      normal_sprites_[i].set_alpha(alpha());
      normal_sprites_[i].Draw(coordinate_system.Translate(p));
    }
  }
}


#pragma mark - InputHandler

bool MultiSelect::HandleInputEvent(InputEvent const &event,
                                   CoordinateSystem const &coordinate_system) {
  if (event.action() == InputEvent::kActionDown && event.HasLocation()) {
    for (int i = 0; i < normal_sprites_.size(); i++) {
      double x = positions_x_[i];
      double y = positions_y_[i];
      GameSize size = normal_sprites_[i].content_size();
      GamePoint touchPoint = event.location();
      if (touchPoint.x >= x && touchPoint.y >= y && touchPoint.x < x + size.width &&
          touchPoint.y < y + size.height) {
        if (selected_value_ != i) {
          selected_value_ = i;
          click_sound_->Play();
        };
        return true;
      }
    }
  }
  return false;
}
