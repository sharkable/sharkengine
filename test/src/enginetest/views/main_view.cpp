//
//  main_view.cpp
//  SharkEngine
//
//  Created by Jon Sharkey on 2/12/13.
//  Copyright (c) 2013 Jon Sharkey. All rights reserved.
//

#include "enginetest/views/main_view.h"

#include "sharkengine/entities/simple_item.h"
#include "sharkengine/game_engine.h"
#include "sharkengine/sprite.h"

MainView::MainView(GameEngine *game_engine) : EngineView(game_engine) {
  Sprite stripes_image(game_engine, "stripes");
  AddEntity(new SimpleItem(stripes_image, game_point_make(10, 10)));
}
