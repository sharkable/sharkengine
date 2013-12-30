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


GameRect SimpleItem::Rect() {
  SpriteAnchor anchor = sprites_[sprite_].anchor();
  switch (anchor) {
    case kSpriteAnchorTopLeft:
      return GameRect(position(), sprites_[sprite_].content_size());
    case kSpriteAnchorCenter:
      GameSize content_size = sprites_[sprite_].content_size();
      GamePoint origin = position() - GamePoint(content_size.width / 2.f,
                                                content_size.height / 2.f);
      return GameRect(origin, content_size);
  }
}


#pragma mark - Renderer

void SimpleItem::Render(CoordinateSystem const &coordinate_system) {
  sprites_[sprite_].Draw(position() + coordinate_system.origin(),
                         angle() + coordinate_system.angle(), alpha(), zoom());
}
