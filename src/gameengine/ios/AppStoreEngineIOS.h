//
//  AppStoreEngineIOS.h
//  GameEngine
//
//  Created by Jon Sharkey on 2013-03-20.
//  Copyright 2013 Sharkable. All rights reserved.
//

#import "gameengine/app_store_engine.h"

#ifndef GAMEENGINE_IOS_APPSTOREENGINEIOS_H_
#define GAMEENGINE_IOS_APPSTOREENGINEIOS_H_

class AppStoreEngineIOS : public AppStoreEngine {
 public:
  void AskForRate(std::string app_name, std::string app_id);
  void AskForUpgrade(std::string app_name, std::string app_id);
};

#endif
