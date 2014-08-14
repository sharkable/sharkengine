//
//  IOSAppStoreModule.h
//  SharkEngine
//
//  Created by Jon Sharkey on 2013-03-20.
//  Copyright 2013 Sharkable. All rights reserved.
//

#import "gameengine/modules/app_store_module.h"

#ifndef GAMEENGINE_APPLE_MODULES_IOS_IOSAPPSTOREMODULE_H_
#define GAMEENGINE_APPLE_MODULES_IOS_IOSAPPSTOREMODULE_H_

@class PopupHandler;

class IOSAppStoreModule : public AppStoreModule {
 public:
  IOSAppStoreModule();
  ~IOSAppStoreModule();

  void AskForRate();
  void AskForUpgrade(std::string app_name, std::string purchase_id,
                     AppStoreModuleDelegate *delegate);

  // Module
  bool IsImplemented() { return true; };

 private:
  PopupHandler *popup_handler_;
};

#endif
