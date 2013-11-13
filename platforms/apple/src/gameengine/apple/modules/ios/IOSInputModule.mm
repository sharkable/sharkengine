//
//  IOSInputModule.mm
//  GameEngine
//
//  Created by Jon Sharkey on 2013-11-13.
//  Copyright 2013 Sharkable. All rights reserved.
//

#include "gameengine/apple/modules/ios/IOSInputModule.h"

IOSInputModule::IOSInputModule()
    : device_angle_(0){
  motion_manager_ = [[CMMotionManager alloc] init];
  motion_manager_.accelerometerUpdateInterval = 1.0 / 60.0;
  operation_queue_ = [[NSOperationQueue alloc] init];
}

IOSInputModule::~IOSInputModule() {
  [motion_manager_ release];
  [operation_queue_ release];
}

void IOSInputModule::TurnOnRotationUpdates() {
  [motion_manager_ startDeviceMotionUpdatesToQueue:operation_queue_
      withHandler:^(CMDeviceMotion *motion, NSError *error) {
          device_angle_ = -atan2f(motion.gravity.y, motion.gravity.x) * 180.f / M_PI;
      }
  ];
}

void IOSInputModule::TurnOffRotationUpdates() {
  [motion_manager_ stopDeviceMotionUpdates];
}
