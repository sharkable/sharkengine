//
//  button.h
//  SharkEngine
//
//  Created by Jon Sharkey on 2010-04-30.
//  Copyright 2010 Sharkable. All rights reserved.
//

#ifndef SHARKENGINE_ENTITIES_BUTTON_H_
#define SHARKENGINE_ENTITIES_BUTTON_H_

#include <vector>

#include "sharksound/sound_controller.h"

#include "sharkengine/coordinates/coordinate_types.h"
#include "sharkengine/entities/animatable.h"
#include "sharkengine/input/input_handler.h"
#include "sharkengine/render/renderer.h"
#include "sharkengine/sprite.h"


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

class Button : public Animatable, public Renderer, public InputHandler {
 public:
  Button(SharkEngine &shark_engine);
  Button(SharkEngine &shark_engine, Sprite normal_sprite, Sprite pressed_sprite,
         GamePoint position);
  ~Button();

  // Renderer
  virtual void Render(CoordinateSystem const &coordinate_system);

  // InputHandler
  virtual bool HandleInputEvent(InputEvent const &event, CoordinateSystem const &coordinate_system);

  bool ContainsPoint(GamePoint p);

  void set_normal_sprite(Sprite normal_sprite) { normal_sprite_ = normal_sprite; }
  void set_pressed_sprite(Sprite pressed_sprite) { pressed_sprite_ = pressed_sprite; }
  void set_pressed_offset(GamePoint offset) { pressed_offset_ = offset; }
  void set_delegate(ButtonDelegate *delegate) { delegate_ = delegate; }
  ButtonState state() { return state_; }
  GameSize size() { return normal_sprite_.content_size(); }

 private:
  void Init();

  SharkEngine &shark_engine_;
  Sprite normal_sprite_;
  Sprite pressed_sprite_;
  GamePoint pressed_offset_;
  ButtonState state_;
  ButtonDelegate *delegate_;
  InputEvent::Id start_touch_;
  SharkSound::Sound *beep_sound_;
};

#endif
