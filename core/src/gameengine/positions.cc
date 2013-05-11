//
//  positions.cc
//  GameEngine
//
//  Created by Jon Sharkey on 2013-02-19.
//  Copyright 2013 Sharkable. All rights reserved.
//

#include "gameengine/positions.h"

#include "thirdparty/tinyxml2/tinyxml2.h"

#include "gameengine/asset_reader.h"

double str2double(const char *str) {
  char *end_ptr;
  double value = strtod(str, &end_ptr);
  if (*end_ptr) return 0;
  return value;
}

void Positions::LoadFile(AssetReader &asset_reader) {
  tinyxml2::XMLDocument doc;

  char *data = new char[asset_reader.Size() + 1];
  asset_reader.Read(data, sizeof(char), asset_reader.Size());
  data[asset_reader.Size()] = '\0';
  assert(!doc.Parse(data));
  delete data;

  tinyxml2::XMLNode *positionsNode = doc.FirstChild();
  assert(!strcmp("positions", positionsNode->ToElement()->Name()));

  tinyxml2::XMLNode *position = positionsNode->FirstChild();
  while (position) {
    const char *name = position->ToElement()->Attribute("name");
    double x = str2double(position->FirstChildElement("x")->GetText());
    double y = str2double(position->FirstChildElement("y")->GetText());
    assert(positions_.find(name) == positions_.end());
    positions_[name] = game_point_make(x, y);

    position = position->NextSibling();
  }
}
