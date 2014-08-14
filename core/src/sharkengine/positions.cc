//
//  positions.cc
//  SharkEngine
//
//  Created by Jon Sharkey on 2013-02-19.
//  Copyright 2013 Sharkable. All rights reserved.
//

#include "sharkengine/positions.h"

#include "sharkengine/asset_reader.h"
#include "sharkengine/thirdparty/tinyxml2/tinyxml2.h"

void Positions::LoadFile(AssetReader &asset_reader) {
  tinyxml2::XMLDocument doc;

  char *data = new char[asset_reader.Size() + 1];
  asset_reader.Read(data, sizeof(char), asset_reader.Size());
  data[asset_reader.Size()] = '\0';
  bool successful_parse = !doc.Parse(data);
  if (!successful_parse) {
    assert(false);
  }
  delete[] data;

  tinyxml2::XMLNode *positionsNode = doc.FirstChild();
  assert(!strcmp("positions", positionsNode->ToElement()->Name()));

  tinyxml2::XMLNode *position = positionsNode->FirstChild();
  while (position) {
    const char *name = position->ToElement()->Attribute("name");
    double x = strtod(position->FirstChildElement("x")->GetText(), NULL);
    double y = strtod(position->FirstChildElement("y")->GetText(), NULL);
    assert(positions_.find(name) == positions_.end());
    positions_[name] = GamePoint(x, y);

    position = position->NextSibling();
  }
}
