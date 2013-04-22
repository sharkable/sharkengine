//
//  game_engine_factory_ios.h
//  GameEngine
//
//  Created by Jon Sharkey on 2013-04-22.
//  Copyright 2013 Sharkable. All rights reserved.
//

#ifndef GAMEENGINE_GAMEENGINEFACTORYIOS_H_
#define GAMEENGINE_GAMEENGINEFACTORYIOS_H_

#include <string>

#include "gameengine/game_engine_factory.h"

class GameEngineFactoryIOS : public GameEngineFactory {
 public:
  sp<AssetReader> createAssetReader(std::string filename);
};

#endif
