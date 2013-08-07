//
//  android_game_engine_factory.h
//  GameEngine
//
//  Created by Jon Sharkey on 2013-04-19.
//  Copyright 2013 Sharkable. All rights reserved.
//

#ifndef GAMEENGINE_ANDROID_MODULES_GAMEENGINEFACTORY_H_
#define GAMEENGINE_ANDROID_MODULES_GAMEENGINEFACTORY_H_

#include <string>

#include "gameengine/game_engine_factory.h"

class AndroidGameEngineFactory : public GameEngineFactory {
 public:
  sp<AssetReader> createAssetReader(std::string filename);
};

#endif
