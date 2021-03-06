//
//  simple_item.h
//  SharkEngine
//
//  Created by Jon Sharkey on 2010-04-30.
//  Copyright 2010 Sharkable. All rights reserved.
//

#ifndef SHARKENGINE_ENTITIES_SIMPLEITEM_H_
#define SHARKENGINE_ENTITIES_SIMPLEITEM_H_

#include <vector>

#include "sharkengine/coordinates/coordinate_types.h"
#include "sharkengine/entities/animatable.h"
#include "sharkengine/render/renderer.h"
#include "sharkengine/sprite.h"

class SimpleItem : public Animatable, public Renderer {
 public:
  SimpleItem();
  SimpleItem(Sprite sprite, GamePoint position);
  SimpleItem(std::vector<Sprite> sprites, GamePoint position);
  ~SimpleItem();

  GameRect Rect();

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
