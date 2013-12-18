//
//  app_store_module.h
//  GameEngine
//
//  Created by Jon Sharkey on 2013-03-20.
//  Copyright 2013 Sharkable. All rights reserved.
//

#ifndef GAMEENGINE_APPSTOREMODULE_H_
#define GAMEENGINE_APPSTOREMODULE_H_

#include "gameengine/module.h"

class AppStoreModuleDelegate {
 public:
  virtual void UpgradeSucceeded() = 0;
};

class AppStoreModule : public Module {
 public:
  virtual void AskForRate() {};
  virtual void AskForUpgrade(std::string app_name, std::string app_id,
                             AppStoreModuleDelegate *delegate) {};
};

#endif
