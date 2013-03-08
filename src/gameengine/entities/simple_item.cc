//
//  simple_item.cc
//  GameEngine
//
//  Created by Jon Sharkey on 2010-04-30.
//  Copyright 2010 Sharkable. All rights reserved.
//

#import "gameengine/entities/simple_item.h"

#import "gameengine/resource_loader.h"

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
    ResourceLoader::Instance().ReleaseResource(sprites_[i].texture());
  }
}


// ViewEntity

void SimpleItem::Render() {
  sprites_[sprite_].Draw(position(), angle(), alpha(), zoom());
}
