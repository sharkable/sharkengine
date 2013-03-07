//
//  positions.cc
//  GameEngine
//
//  Created by Jon Sharkey on 2/19/13.
//
//

#include "gameengine/positions.h"

#include "thirdparty/tinyxml2/tinyxml2.h"

double str2double(const char *str) {
  char *end_ptr;
  double value = strtod(str, &end_ptr);
  if (*end_ptr) return 0;
  return value;
}

void Positions::LoadFile(std::string filename) {
  tinyxml2::XMLDocument doc;
  assert(!doc.LoadFile(filename.c_str()));
  tinyxml2::XMLNode *positionsNode = doc.FirstChild();
  assert(!strcmp("positions", positionsNode->ToElement()->Name()));

  tinyxml2::XMLNode *position = positionsNode->FirstChild();
  while (position) {
    const char *name = position->ToElement()->Attribute("name");
    double x = str2double(position->FirstChildElement("x")->GetText());
    double y = str2double(position->FirstChildElement("y")->GetText());
    positions_[name] = game_point_make(x, y);

    position = position->NextSibling();
  }
}
