//
//  multi_select.h
//  AirHockey
//
//  Created by Jonathan Sharkey on 10-04-30.
//  Copyright 2010 Sharkable. All rights reserved.
//

#ifndef AIRHOCKEY_GAMEENGINE_ENTITIES_MULTISELECT_H_
#define AIRHOCKEY_GAMEENGINE_ENTITIES_MULTISELECT_H_

#include <vector>
using namespace std;

#include "gameengine/view_entity.h"

class Sprite;
struct GamePoint;

class MultiSelect : public ViewEntity {
 public:
  MultiSelect() {}
  ~MultiSelect();

  void Add(Sprite normal_sprite, Sprite selected_sprite, GamePoint position);

  // ViewEntity
  void Update() {}
  void Render();
  void TouchesBegan(vector<Touch> touches);

  // Accessors
  int selected_value() { return selected_value_; };
  void set_selected_value(int selected_value) { selected_value_ = selected_value; }

 private:
  vector<Sprite> normal_sprites_;
  vector<Sprite> selected_sprites_;
  vector<double> positions_x_;
  vector<double> positions_y_;
  int selected_value_;
};

#endif
