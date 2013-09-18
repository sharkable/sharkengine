//
//  IOSLabelFactoryModule.h
//  GameEngine
//
//  Created by Jon Sharkey on 2013-09-18.
//  Copyright 2013 Sharkable. All rights reserved.
//

#ifndef GAMEENGINE_APPLE_MODULES_IOS_IOSLABELFACTORYMODULE_H_
#define GAMEENGINE_APPLE_MODULES_IOS_IOSLABELFACTORYMODULE_H_

#include "gameengine/modules/label_factory_module.h"

#include <string>
#import <UIKit/UIKit.h>

#include "gameengine/coordinate_types.h"

class IOSLabelFactoryModule : public LabelFactoryModule {
 public:
  IOSLabelFactoryModule(UIView *parent_view);
  ~IOSLabelFactoryModule();

  // LabelFactoryModule
  sp<Label> CreateLabel(std::string text, GamePoint position);

 private:
  UIView *parent_view_;
};

#endif
