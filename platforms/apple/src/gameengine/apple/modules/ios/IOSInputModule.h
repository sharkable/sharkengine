//
//  IOSInputModule.h
//  GameEngine
//
//  Created by Jon Sharkey on 2013-11-13.
//  Copyright 2013 Sharkable. All rights reserved.
//

#ifndef GAMEENGINE_APPLE_MODULES_IOS_IOSINPUTMODULE_H_
#define GAMEENGINE_APPLE_MODULES_IOS_IOSINPUTMODULE_H_

#include "gameengine/modules/input_module.h"

@class OrientationListener;

class IOSInputModule : public InputModule {
 public:
  IOSInputModule();
  ~IOSInputModule();

  void set_device_angle(float device_angle) { device_angle_ = device_angle; }

  // InputModule
  void TurnOnRotationUpdates();
  void TurnOffRotationUpdates();
  float device_angle() { return device_angle_; }

 private:
  float device_angle_;
  OrientationListener *orientation_listener_;
};

#endif
