//
//  button.h
//  GameEngine
//
//  Created by Jon Sharkey on 2010-04-30.
//  Copyright 2010 Sharkable. All rights reserved.
//

#ifndef GAMEENGINE_ENTITIES_BUTTON_H_
#define GAMEENGINE_ENTITIES_BUTTON_H_

#include <vector>

#include "sharksound/sound_controller.h"

#include "gameengine/entities/animatable.h"
#include "gameengine/coordinate_types.h"
#include "gameengine/sprite.h"


class Touch;

typedef enum {
  kButtonStateNormal,
  kButtonStatePressed
} ButtonState;

class Button;

class ButtonDelegate {
 public:
  virtual void ButtonDown(Button *button) {};
  virtual void ButtonUp(Button *button) {};
};

class Button : public Animatable {
 public:
  Button(GameEngine &game_engine);
  Button(GameEngine &game_engine, Sprite normal_sprite, Sprite pressed_sprite, GamePoint position);
  ~Button();

  // ViewEntity
  void Render(GamePoint render_offset, float render_angle);
  bool TouchBegan(GamePoint offset, Touch touch);
  void TouchEnded(GamePoint offset, Touch touch);
  GameRect Rect();

  bool ContainsPoint(GamePoint p);

  void set_normal_sprite(Sprite normal_sprite) { normal_sprite_ = normal_sprite; }
  void set_pressed_sprite(Sprite pressed_sprite) { pressed_sprite_ = pressed_sprite; }
  void set_pressed_offset(GamePoint offset) { pressed_offset_ = offset; }
  void set_delegate(ButtonDelegate *delegate) { delegate_ = delegate; }
  ButtonState state() { return state_; }
  GameSize size() { return normal_sprite_.content_size(); }

 private:
  void Init();

  GameEngine &game_engine_;
  Sprite normal_sprite_;
  Sprite pressed_sprite_;
  GamePoint pressed_offset_;
  ButtonState state_;
  ButtonDelegate *delegate_;
  void *start_touch_;
  SharkSound::Sound *beep_sound_;
};

#endif
