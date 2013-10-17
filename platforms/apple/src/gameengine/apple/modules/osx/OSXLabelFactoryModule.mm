//
//  OSXLabelFactoryModule.mm
//  GameEngine
//
//  Created by Jon Sharkey on 2013-10-17.
//  Copyright 2013 Sharkable. All rights reserved.
//

#include "gameengine/apple/modules/osx/OSXLabelFactoryModule.h"

#include "gameengine/apple/entities/osx/OSXLabel.h"

using namespace std;

OSXLabelFactoryModule::OSXLabelFactoryModule() {
}

OSXLabelFactoryModule::~OSXLabelFactoryModule() {
}


// LabelFactoryModule

Label * OSXLabelFactoryModule::CreateLabel(string text, GamePoint position) {
  return new OSXLabel(text, position);
}
