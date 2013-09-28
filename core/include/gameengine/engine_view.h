//
//  engine_view.h
//  GameEngine
//
//  Created by Jon Sharkey on 2010-04-10.
//  Copyright 2010 Sharkable. All rights reserved.
//

#ifndef GAMEENGINE_ENGINEVIEW_H_
#define GAMEENGINE_ENGINEVIEW_H_

#include <vector>

#include "gameengine/view_entity.h"
#include "gameengine/datastructures/staged_vector.h"

class GameEngine;
class Touch;

class EngineView {
 public:
  EngineView(GameEngine *game_engine);
  virtual ~EngineView() {}

  virtual void ViewDidGainFocus() {}
  virtual void ViewDidLoseFocus() {}
  virtual void Update();
  virtual void Render();
  virtual void NotifyPause() {}
  virtual bool IsCapturingTouches();
  virtual void TouchesBegan(std::vector<Touch> touches);
  virtual void TouchesMoved(std::vector<Touch> touches);
  virtual void TouchesEnded(std::vector<Touch> touches);
  virtual void TouchTapped(Touch touch);
  virtual void ClearTouches();
  virtual void HandleMouseDelta(float delta_x, float delta_y);
  virtual bool HandleBackButton();  // If this returns false, the app is quit.
  virtual void HandlePauseButton() {}
  // If you add an entity using this method, then this EngineView is responsible for releasing this
  // object.
  void AddEntity(ViewEntity *entity, bool managed_memory = true);
  void InsertEntityBefore(ViewEntity *entity, ViewEntity *existing_entity,
                          bool managed_memory = true);
  void InsertEntityAfter(ViewEntity *entity, ViewEntity *existing_entity,
                         bool managed_memory = true);
  void RemoveEntity(ViewEntity *entity);

  GameEngine *game_engine() { return game_engine_; }
  bool is_visible() { return is_visible_; }

 private:
  void set_is_visible(bool is_visible) { is_visible_ = is_visible; }
  friend class GameEngine;

  GameEngine *game_engine_;  // weak
  StagedVector<ViewEntity> entities_;
  bool is_visible_;
};

#endif
