//
//  ad_module.h
//  GameEngine
//
//  Created by Jon Sharkey on 2012-02-25.
//  Copyright 2012 Sharkable. All rights reserved.
//

#ifndef GAMEENGINE_ADMODULE_H_
#define GAMEENGINE_ADMODULE_H_

#include <string>

#include "gameengine/coordinate_types.h"
#include "gameengine/module.h"

class AdModule : public Module {
 public:
  virtual void SetPublisherId(std::string publisher_id) {};
  virtual void SetAdAtPoint(ScreenPoint point) {};
  virtual void RemoveAd() {};
  virtual void PrepareFullScreenAd() {};
  virtual bool ShowFullScreenAd() { return false; };
  virtual bool IsShowingFullScreenAd() { return false; };
};

#endif
