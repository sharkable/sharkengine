//
//  AppStoreEngineIOS.h
//  GameEngine
//
//  Created by Jon Sharkey on 2013-03-20.
//  Copyright 2013 Sharkable. All rights reserved.
//

#import "gameengine/modules/app_store_engine.h"

#ifndef GAMEENGINE_IOS_APPSTOREENGINEIOS_H_
#define GAMEENGINE_IOS_APPSTOREENGINEIOS_H_

@class PopupHandler;

class AppStoreEngineIOS : public AppStoreEngine {
 public:
  AppStoreEngineIOS();
  ~AppStoreEngineIOS();

  void AskForRate();
  void AskForUpgrade(std::string app_name, std::string purchase_id);

 private:
  PopupHandler *popup_handler_;
};

#endif
