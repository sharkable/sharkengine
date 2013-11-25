//
//  IOSInputModule.mm
//  GameEngine
//
//  Created by Jon Sharkey on 2013-11-13.
//  Copyright 2013 Sharkable. All rights reserved.
//

#include "gameengine/apple/modules/ios/IOSInputModule.h"

@interface OrientationListener : NSObject
@property (nonatomic, assign) IOSInputModule *inputModule;
@end

@implementation OrientationListener

@synthesize inputModule;

- (void)deviceOrientationDidChange {
  float angle;
  switch ([UIDevice currentDevice].orientation) {
    case UIDeviceOrientationPortrait:
      angle = 90.f;
      break;
    case UIDeviceOrientationPortraitUpsideDown:
      angle = 270.f;
      break;
    case UIDeviceOrientationLandscapeLeft:
      angle = 180.f;
      break;
    case UIDeviceOrientationLandscapeRight:
      angle = 0.f;
      break;
    default:
      return;
  }
  self.inputModule->set_device_angle(angle);
}

@end

IOSInputModule::IOSInputModule() : device_angle_(0.f) {
  orientation_listener_ = [[OrientationListener alloc] init];
  orientation_listener_.inputModule = this;
  [[NSNotificationCenter defaultCenter] addObserver:orientation_listener_
                                           selector:@selector(deviceOrientationDidChange)
                                               name:UIDeviceOrientationDidChangeNotification
                                             object:nil];
}

IOSInputModule::~IOSInputModule() {
  [orientation_listener_ release];
}


#pragma mark - InputModule

void IOSInputModule::TurnOnRotationUpdates() {
  [[UIDevice currentDevice] beginGeneratingDeviceOrientationNotifications];
}

void IOSInputModule::TurnOffRotationUpdates() {
  [[UIDevice currentDevice] endGeneratingDeviceOrientationNotifications];
}
