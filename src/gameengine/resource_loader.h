//
//  resource_loader.h
//  AirHockey
//
//  Created by Jonathan Sharkey on 09-09-28.
//  Copyright 2009 Sharkable. All rights reserved.
//

#ifndef AIRHOCKEY_GAMEENGINE_RESOURCELOADER_H_
#define AIRHOCKEY_GAMEENGINE_RESOURCELOADER_H_

#include <map>

#include "opengl/Texture2D.h"

class ResourceLoader {
 public:
  static ResourceLoader &Instance();
  Texture2D TextureWithName(std::string name);
  void ReleaseResource(std::string name);
  void ReleaseResource(Texture2D resource);

 private:
  Texture2D Texture(std::string filename);
  
  std::map<std::string, Texture2D> resources_;
  std::map<std::string, int> resource_counter_;
};

#endif
