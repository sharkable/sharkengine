//
//  IOSLabelFactoryModule.mm
//  GameEngine
//
//  Created by Jon Sharkey on 2013-09-18.
//  Copyright 2013 Sharkable. All rights reserved.
//

#include "gameengine/apple/modules/ios/IOSLabelFactoryModule.h"

#include "gameengine/apple/entities/ios/IOSLabel.h"

using namespace std;

IOSLabelFactoryModule::IOSLabelFactoryModule(UIView *parent_view) {
  parent_view_ = [parent_view retain];
}

IOSLabelFactoryModule::~IOSLabelFactoryModule() {
  [parent_view_ release];
}


// LabelFactoryModule

sp<Label> IOSLabelFactoryModule::CreateLabel(string text, GamePoint position) {
  return sp<Label>(new IOSLabel(text, position, parent_view_));
}
