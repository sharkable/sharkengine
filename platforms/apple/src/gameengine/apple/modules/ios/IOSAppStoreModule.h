//
//  IOSAppStoreEngine.h
//  GameEngine
//
//  Created by Jon Sharkey on 2013-03-20.
//  Copyright 2013 Sharkable. All rights reserved.
//

#import "gameengine/modules/app_store_engine.h"

#ifndef GAMEENGINE_APPLE_MODULES_IOS_IOSAPPSTOREENGINE_H_
#define GAMEENGINE_APPLE_MODULES_IOS_IOSAPPSTOREENGINE_H_

@class PopupHandler;

class IOSAppStoreEngine : public AppStoreEngine {
 public:
  IOSAppStoreEngine();
  ~IOSAppStoreEngine();

  void AskForRate();
  void AskForUpgrade(std::string app_name, std::string purchase_id,
                     AppStoreEngineDelegate *delegate);

  // Module
  bool IsImplemented() { return true; };

 private:
  PopupHandler *popup_handler_;
};

#endif
