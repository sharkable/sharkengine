//
//  OSXLabel.h
//  GameEngine
//
//  Created by Jon Sharkey on 2013-10-17.
//  Copyright 2013 Sharkable. All rights reserved.
//

#include "gameengine/apple/entities/osx/OSXLabel.h"

#include "gameengine/engine_view.h"
#include "gameengine/apple/TypeUtil.h"

using std::string;

OSXLabel::OSXLabel(string text, GamePoint position)
: Label(position) {
}

OSXLabel::~OSXLabel() {
}

const std::string & OSXLabel::Text() {
  return text_;
}

void OSXLabel::SetText(const std::string &text) {
  text_ = text;
}

void OSXLabel::SetFontSize(float font_size) {
}


// ViewEntity

void OSXLabel::Render(GamePoint offset) {
}
