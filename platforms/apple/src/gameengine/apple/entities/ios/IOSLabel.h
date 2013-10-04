//
//  IOSLabel.h
//  GameEngine
//
//  Created by Jon Sharkey on 2013-09-18.
//  Copyright 2013 Sharkable. All rights reserved.
//

#ifndef GAMEENGINE_APPLE_ENTITIES_IOS_IOSLABEL_H_
#define GAMEENGINE_APPLE_ENTITIES_IOS_IOSLABEL_H_

#include "gameengine/entities/label.h"

#include <string>
#import <UIKit/UIKit.h>

#include "gameengine/coordinate_types.h"

class IOSLabel : public Label {
 public:
  IOSLabel(std::string text, GamePoint position, UIView *parent_view);
  ~IOSLabel();

  // Label
  const std::string & Text();
  void SetText(const std::string &text);
  void SetFontSize(float font_size);

  // ViewEntity
  void Render(GamePoint offset);

 private:
  std::string text_;
  UILabel *uikit_label_;
  UIView *parent_view_;
};

#endif
