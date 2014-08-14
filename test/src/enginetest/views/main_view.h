//
//  main_view.h
//  SharkEngine
//
//  Created by Jon Sharkey on 2/12/13.
//  Copyright (c) 2013 Jon Sharkey. All rights reserved.
//

#ifndef ENGINETEST_VIEWS_MAINVIEW_H_
#define ENGINETEST_VIEWS_MAINVIEW_H_

#include "sharkengine/engine_view.h"

class GameEngine;

class MainView : public EngineView {
 public:
  MainView(GameEngine *game_engine);
};

#endif
