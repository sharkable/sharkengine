//
//  OSXLabel.mm
//  GameEngine
//
//  Created by Jon Sharkey on 2013-10-17.
//  Copyright 2013 Sharkable. All rights reserved.
//

#ifndef GAMEENGINE_APPLE_ENTITIES_OSX_OSXLABEL_H_
#define GAMEENGINE_APPLE_ENTITIES_OSX_OSXLABEL_H_

#include "gameengine/entities/label.h"

#include <string>

#include "gameengine/coordinate_types.h"

class OSXLabel : public Label {
public:
  OSXLabel(std::string text, GamePoint position);
  ~OSXLabel();

  // Label
  const std::string & Text();
  void SetText(const std::string &text);
  void SetFontSize(float font_size);

  // ViewEntity
  void Render(GamePoint offset);

private:
  std::string text_;
};

#endif
