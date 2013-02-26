//
//  simple_item.h
//  GameEngine
//
//  Created by Jonathan Sharkey on 10-04-30.
//  Copyright 2010 Sharkable. All rights reserved.
//

#ifndef AIRHOCKEY_GAMEENGINE_ENTITIES_SIMPLEITEM_H_
#define AIRHOCKEY_GAMEENGINE_ENTITIES_SIMPLEITEM_H_

#include <vector>
using namespace std;

#include "gameengine/entities/animatable.h"
#include "gameengine/sprite.h"

class SimpleItem : public Animatable {
 public:
  SimpleItem();
  SimpleItem(Sprite sprite, GamePoint position);
  SimpleItem(vector<Sprite> sprites, GamePoint position);
  ~SimpleItem();

  // ViewEntity
  void Update() {}
  void Render();

  // Accessors
  void set_sprites(vector<Sprite> sprites) { sprites_ = sprites; }
  int sprite() { return sprite_; }
  void set_sprite(int sprite) { sprite_ = sprite; }
  void add_sprite(Sprite sprite) { sprites_.push_back(sprite); }
  GameSize size() { return sprites_[sprite_].content_size(); }

 private:
  vector<Sprite> sprites_;
  int sprite_;
};

#endif
