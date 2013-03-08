//
//  ResourceLoader.m
//  GameEngine
//
//  Created by Jon Sharkey on 2009-09-28.
//  Copyright 2009 Sharkable. All rights reserved.
//

#include "gameengine/resource_loader.h"

using std::map;
using std::string;

ResourceLoader instance__;

ResourceLoader &ResourceLoader::Instance() {
  return instance__;          
}

Texture2D ResourceLoader::TextureWithName(string name) {
  if (resource_counter_[name] == 0) {
    Texture2D tex = Texture(name);
    resource_counter_[name]++;
    resources_[name] = tex;
    return tex;
  }

  Texture2D texture = resources_[name];
  resource_counter_[name]++;

  return texture;  
}

void ResourceLoader::ReleaseResource(string name) {
  int count = resource_counter_[name];
  if (count == 0) {
    return;
  } else if (count == 1) {
    resources_[name].Delete();
    resources_.erase(name);
    resource_counter_.erase(name);
  } else {
    resource_counter_[name] = count - 1;
  }
}

void ResourceLoader::ReleaseResource(Texture2D resource) {
  for (auto i = resources_.begin(); i != resources_.end(); i++) {
    if (i->second.name() == resource.name()) {
      ReleaseResource(i->first);
      return;
    }
  }
  assert(false);
}
