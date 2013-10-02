//
//  IOSLabel.mm
//  GameEngine
//
//  Created by Jon Sharkey on 2013-09-18.
//  Copyright 2013 Sharkable. All rights reserved.
//

#include "gameengine/apple/entities/ios/IOSLabel.h"

#include "gameengine/engine_view.h"
#include "gameengine/apple/TypeUtil.h"

using std::string;

IOSLabel::IOSLabel(string text, GamePoint position, UIView *parent_view)
    : Label(position) {
  parent_view_ = [parent_view retain];
  uikit_label_ = [[UILabel alloc] init];
  uikit_label_.textColor = [UIColor whiteColor];
  uikit_label_.numberOfLines = 0;
  uikit_label_.lineBreakMode = NSLineBreakByWordWrapping;
  SetText(text);
}

IOSLabel::~IOSLabel() {
  [uikit_label_ removeFromSuperview];
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
  // TODO The label won't go away if the view is removed and the |EngineView| is not desctructed.
  // reconsider the callback solution.
  if (uikit_label_.superview == parent_view_) {
    if (!view() || !view()->is_visible()) {
      [uikit_label_ removeFromSuperview];
    }
  } else {
    if (view() && view()->is_visible()) {
      [parent_view_ addSubview:uikit_label_];
    }
  }
  CGRect frame = uikit_label_.frame;
  frame.origin.x = (position().x + offset.x) / 2;  // TODO. Do a proper conversion.
  frame.origin.y = (position().y + offset.y) / 2;
  uikit_label_.frame = frame;
}
