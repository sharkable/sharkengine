//
//  simple_item.cc
//  GameEngine
//
//  Created by Jon Sharkey on 2010-04-30.
//  Copyright 2010 Sharkable. All rights reserved.
//

#include "gameengine/entities/simple_item.h"

#include "gameengine/resource_loader.h"

using std::vector;

SimpleItem::SimpleItem()
    : Animatable(),
      sprite_(0) {
}

SimpleItem::SimpleItem(Sprite sprite, GamePoint position)
    : Animatable(position),
      sprite_(0) {
  sprites_.push_back(sprite);
}

SimpleItem::SimpleItem(vector<Sprite> sprites, GamePoint position)
    : Animatable(position),
      sprites_(sprites),
      sprite_(0) {
}

SimpleItem::~SimpleItem() {
  for (int i = 0; i < sprites_.size(); i++) {
    // TODO ResourceLoader::Instance().ReleaseResource(sprites_[i].texture());
  }
}


#pragma mark - ViewEntity

void SimpleItem::Render(GamePoint render_offset, float render_angle) {
  sprites_[sprite_].Draw(position() + render_offset, angle() + render_angle, alpha(), zoom());
}

GameRect SimpleItem::Rect() {
  SpriteAnchor anchor = sprites_[sprite_].anchor();
  switch (anchor) {
    case kSpriteAnchorTopLeft:
      return game_rect_make(position(), sprites_[sprite_].content_size());
    case kSpriteAnchorCenter:
      GameSize content_size = sprites_[sprite_].content_size();
      GamePoint origin = position() - game_point_make(content_size.width / 2.f,
                                                      content_size.height / 2.f);
      return game_rect_make(origin, content_size);
  }
}
