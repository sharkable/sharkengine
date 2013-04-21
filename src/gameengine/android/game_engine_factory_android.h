//
//  game_engine_factory_android.h
//  GameEngine
//
//  Created by Jon Sharkey on 2013-04-19.
//  Copyright 2013 Sharkable. All rights reserved.
//

#ifndef GAMEENGINE_GAMEENGINEFACTORYANDROID_H_
#define GAMEENGINE_GAMEENGINEFACTORYANDROID_H_

#include <string>

#include "gameengine/game_engine_factory.h"

class GameEngineFactoryAndroid : public GameEngineFactory {
 public:
  sp<AssetReader> createAssetReader(std::string filename);
};

#endif
