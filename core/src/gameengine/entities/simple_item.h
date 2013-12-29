//
//  simple_item.h
//  GameEngine
//
//  Created by Jon Sharkey on 2010-04-30.
//  Copyright 2010 Sharkable. All rights reserved.
//

#ifndef GAMEENGINE_ENTITIES_SIMPLEITEM_H_
#define GAMEENGINE_ENTITIES_SIMPLEITEM_H_

#include <vector>

#include "gameengine/coordinates/coordinate_types.h"
#include "gameengine/entities/animatable.h"
#include "gameengine/render/renderer.h"
#include "gameengine/simulation/simulator.h"
#include "gameengine/sprite.h"

class SimpleItem : public Animatable, public Simulator, public Renderer {
 public:
  SimpleItem();
  SimpleItem(Sprite sprite, GamePoint position);
  SimpleItem(std::vector<Sprite> sprites, GamePoint position);
  ~SimpleItem();

  // ViewEntity
  void Render(GamePoint render_offset, float render_angle);
  GameRect Rect();

  // Simulator
  void SimulateStep();

  // Renderer
  void Render(CoordinateSystem const &coordinate_system);

  // Accessors
  void set_sprites(std::vector<Sprite> sprites) { sprites_ = sprites; }
  int sprite() { return sprite_; }
  void set_sprite(int sprite) { sprite_ = sprite; }
  void add_sprite(Sprite sprite) { sprites_.push_back(sprite); }
  GameSize size() { return sprites_[sprite_].content_size(); }

 private:
  std::vector<Sprite> sprites_;
  int sprite_;
};

#endif
