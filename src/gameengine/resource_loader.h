//
//  resource_loader.h
//  GameEngine
//
//  Created by Jon Sharkey on 2009-09-28.
//  Copyright 2009 Sharkable. All rights reserved.
//

#ifndef GAMEENGINE_RESOURCELOADER_H_
#define GAMEENGINE_RESOURCELOADER_H_

#include <map>
#include <string>

#include "opengl/Texture2D.h"

class AssetReader;
class GameEngine;

class ResourceLoader {
 public:
  ResourceLoader(GameEngine &game_engine);

  Texture2D TextureWithName(const std::string &name);
  void ReleaseResource(const std::string &name);
  void ReleaseResource(Texture2D resource);

 private:
  Texture2D Texture(std::string filename);

  GameEngine &game_engine_;
  std::map<std::string, Texture2D> resources_;
  std::map<std::string, int> resource_counter_;
};

#endif
