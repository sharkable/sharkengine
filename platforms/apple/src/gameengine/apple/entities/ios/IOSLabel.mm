//
//  IOSLabel.mm
//  GameEngine
//
//  Created by Jon Sharkey on 2013-09-18.
//  Copyright 2013 Sharkable. All rights reserved.
//

#include "gameengine/apple/entities/ios/IOSLabel.h"

#include "gameengine/apple/TypeUtil.h"

using std::string;

IOSLabel::IOSLabel(string text, GamePoint position, UIView *parent_view)
    : Label(position) {
  parent_view_ = [parent_view retain];
  uikit_label_ = [[UILabel alloc] init];
  [parent_view_ addSubview:uikit_label_];
  SetText(text);
}

IOSLabel::~IOSLabel() {
  [uikit_label_ release];
  [parent_view_ release];
}

const std::string & IOSLabel::Text() {
  return text_;
}

void IOSLabel::SetText(const std::string &text) {
  text_ = text;
  uikit_label_.text = TypeUtil::string2NSString(text);
  [uikit_label_ sizeToFit];
}


// ViewEntity

void IOSLabel::Render(GamePoint offset) {
  CGRect frame = uikit_label_.frame;
  frame.origin.x = position().x / 2;  // TODO. Do a proper conversion.
  frame.origin.y = position().y / 2;
  uikit_label_.frame = frame;
}
