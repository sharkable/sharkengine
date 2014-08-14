//
//  OSXInputModule.cc
//  SharkengineApp
//
//  Created by Jon Sharkey on 8/11/13.
//  Copyright (c) 2013 Jon Sharkey. All rights reserved.
//

#include "gameengine/apple/modules/osx/OSXInputModule.h"

void OSXInputModule::HidePointer() {
  CGDisplayHideCursor(kCGDirectMainDisplay);
}

void OSXInputModule::ShowPointer() {
  CGDisplayShowCursor(kCGDirectMainDisplay);
}
