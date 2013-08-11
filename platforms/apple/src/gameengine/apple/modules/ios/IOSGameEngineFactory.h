//
//  IOSGameEngineFactory.h
//  GameEngine
//
//  Created by Jon Sharkey on 2013-04-22.
//  Copyright 2013 Sharkable. All rights reserved.
//

#ifndef GAMEENGINE_APPLE_MODULES_IOS_IOSGAMEENGINEFACTORY_H_
#define GAMEENGINE_APPLE_MODULES_IOS_IOSGAMEENGINEFACTORY_H_

#include <string>

#include "gameengine/game_engine_factory.h"

class IOSGameEngineFactory : public GameEngineFactory {
 public:
  sp<AssetReader> createAssetReader(std::string filename);
};

#endif
