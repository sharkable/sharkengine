//
//  main_view.h
//  GameEngine
//
//  Created by Jon Sharkey on 2/12/13.
//  Copyright (c) 2013 Jon Sharkey. All rights reserved.
//

#ifndef ENGINETEST_VIEWS_MAINVIEW_H_
#define ENGINETEST_VIEWS_MAINVIEW_H_

#include "gameengine/engine_view.h"

class GameEngine;

class MainView : public EngineView {
 public:
  MainView(sp<GameEngine> game_engine);
};

#endif
