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
using namespace std;

#include "opengl/Texture2D.h"

class ResourceLoader {
 public:
  static ResourceLoader &Instance();
  Texture2D TextureWithName(string name);
  void ReleaseResource(string name);
  void ReleaseResource(Texture2D resource);

 private:
  Texture2D Texture(string filename);
  
  map<string, Texture2D> resources_;
  map<string, int> resource_counter_;
};

#endif
