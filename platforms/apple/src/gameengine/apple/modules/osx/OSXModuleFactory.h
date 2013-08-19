//
//  OSXGameEngineFactory.h
//  GameEngine
//
//  Created by Jon Sharkey on 2013-08-11.
//  Copyright 2013 Sharkable. All rights reserved.
//

#ifndef GAMEENGINE_APPLE_MODULES_OSX_OSXGAMEENGINEFACTORY_H_
#define GAMEENGINE_APPLE_MODULES_OSX_OSXGAMEENGINEFACTORY_H_

#include <string>

#include "gameengine/game_engine_factory.h"

#include "zip.h"

class OSXGameEngineFactory : public GameEngineFactory {
 public:
  OSXGameEngineFactory();
  ~OSXGameEngineFactory();

  sp<AssetReader> createAssetReader(std::string filename);

 private:
  zip *zip_;
};

#endif
