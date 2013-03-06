//
//  button.h
//  AirHockey
//
//  Created by Jonathan Sharkey on 10-04-30.
//  Copyright 2010 Sharkable. All rights reserved.
//

#ifndef GAMEENGINE_ENTITIES_BUTTON_H_
#define GAMEENGINE_ENTITIES_BUTTON_H_

#include "gameengine/entities/animatable.h"
#include "gameengine/game_engine.h"
#include "gameengine/sprite.h"

typedef enum {
  kButtonStateNormal,
  kButtonStatePressed
} ButtonState;

class Button;

class ButtonDelegate {
 public:
  virtual void ButtonPressed(Button *button) = 0;
};

class Button : public Animatable {
 public:
  Button() : state_(kButtonStateNormal) {}
  Button(Sprite normal_sprite, Sprite pressed_sprite, GamePoint position);
  ~Button();
  
  // ViewEntity
  void Render();
  void TouchesBegan(vector<Touch> touches);
  void TouchesEnded(vector<Touch> touches);

  bool ContainsPoint(GamePoint p);

  void set_normal_sprite(Sprite normal_sprite) { normal_sprite_ = normal_sprite; }
  void set_pressed_sprite(Sprite pressed_sprite) { pressed_sprite_ = pressed_sprite; }
  void set_delegate(ButtonDelegate *delegate) { delegate_ = delegate; }
  GameSize size() { return normal_sprite_.content_size(); }
 
 private:
  Sprite normal_sprite_;
  Sprite pressed_sprite_;
  int state_;
  ButtonDelegate *delegate_;
};

#endif
