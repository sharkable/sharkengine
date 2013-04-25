//
//  game_engine_factory.h
//  GameEngine
//
//  Created by Jon Sharkey on 2013-04-19.
//  Copyright 2013 Sharkable. All rights reserved.
//

#ifndef GAMEENGINE_GAMEENGINEFACTORY_H_
#define GAMEENGINE_GAMEENGINEFACTORY_H_

#include <string>

class AssetReader;

class GameEngineFactory {
 public:
  virtual sp<AssetReader> createAssetReader(std::string filename) = 0;
};

#endif
