//
//  IOSInputModule.h
//  GameEngine
//
//  Created by Jon Sharkey on 2013-11-13.
//  Copyright 2013 Sharkable. All rights reserved.
//

#ifndef GAMEENGINE_APPLE_MODULES_IOS_IOSINPUTMODULE_H_
#define GAMEENGINE_APPLE_MODULES_IOS_IOSINPUTMODULE_H_

#import <CoreMotion/CoreMotion.h>

#include "gameengine/modules/input_module.h"

class IOSInputModule : public InputModule {
 public:
  IOSInputModule();
  ~IOSInputModule();

  // InputModule
  void TurnOnRotationUpdates();
  void TurnOffRotationUpdates();
  float device_angle() { return device_angle_; }

 private:
  float device_angle_;
  CMMotionManager *motion_manager_;
  NSOperationQueue *operation_queue_;
};

#endif
