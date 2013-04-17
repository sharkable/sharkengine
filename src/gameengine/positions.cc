//
//  positions.cc
//  GameEngine
//
//  Created by Jon Sharkey on 2013-02-19.
//  Copyright 2013 Sharkable. All rights reserved.
//

#include "gameengine/positions.h"

#include "thirdparty/tinyxml2/tinyxml2.h"

#include "libzip/zip.h"
#include "app.h"

double str2double(const char *str) {
  char *end_ptr;
  double value = strtod(str, &end_ptr);
  if (*end_ptr) return 0;
  return value;
}

void Positions::LoadFile(std::string filename) {
  // TODO: Android only
  struct zip_stat stat;
  zip_stat(APKArchive, filename.c_str(), 0, &stat);
  s_log("POSITION: %s  %d", filename.c_str(), stat.size);
  zip_file *fp = zip_fopen(APKArchive, filename.c_str(), 0);
  char *data = new char[stat.size];
  zip_fread(fp, data, stat.size);

  tinyxml2::XMLDocument doc;
//  assert(!doc.LoadFile(filename.c_str()));
  s_log("trying to parse: %d", doc.Parse(data));
  delete data;
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
