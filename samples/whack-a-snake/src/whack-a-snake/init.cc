//
//  init.cc
//  Whack-a-Snake
//
//  Created by Jon Sharkey on 2014-08-17.
//  Copyright 2014 Sharkable. All rights reserved.
//

#include "sharkengine/platform.h"
#include "sharkengine/resource_loader.h"
#include "sharkengine/shark_engine.h"
#include "sharkengine/coordinates/coordinate_types.h"
#include "sharkengine/modules/ad_module.h"

#include <cstdlib>
#include <ctime>

#include "whack-a-snake/play_view.h"

void sharkengine_init(SharkEngine &shark_engine) {
  srand(static_cast<unsigned int>(time(NULL)));

  switch (shark_engine.platform().texture_group()) {
    case Platform::kTextureGroupIPhone35cmLowRes:
    case Platform::kTextureGroupAndroidLowRes:
    case Platform::kTextureGroupIPadLowRes:
      shark_engine.resource_loader().set_texture_name_extention("");
      break;
    case Platform::kTextureGroupIPhone35cmHighRes:
    case Platform::kTextureGroupIPhone40cmHighRes:
    case Platform::kTextureGroupAndroidHighRes:
    case Platform::kTextureGroupIPadHighRes:
    case Platform::kTextureGroupPCHighRes:
    case Platform::kTextureGroupPCUltraHighRes:
      shark_engine.resource_loader().set_texture_name_extention("@2x");
      break;
  }

  GameSize screen_size = shark_engine.screen_size();
  GameSize game_size(640, 1136);

  shark_engine.set_screen_to_game_point_ratios(1, 1);
  double x_offset =
      (screen_size.width - shark_engine.game_size_to_screen_size(game_size).width) / 2;
  double y_offset =
      (screen_size.height - shark_engine.game_size_to_screen_size(game_size).height) / 2;
  shark_log("offsets: %f %f", x_offset, y_offset);
  shark_engine.set_screen_offset(ScreenPoint(x_offset, y_offset));

  PlayView *view = new PlayView(shark_engine);
  shark_engine.SetSimulator(view);
  shark_engine.SetRenderer(view);
  shark_engine.SetInputHandler(view);
}
