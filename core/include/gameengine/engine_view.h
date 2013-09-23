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

class GameEngine;
class Touch;
class ViewEntity;

class EngineView {
 public:
  EngineView(GameEngine *game_engine);

  virtual void ViewDidGainFocus() {}
  virtual void ViewDidLoseFocus() {}
  virtual void Update();
  virtual void Render();
  virtual void NotifyPause() {}
  virtual bool IsCapturingTouches();
  virtual void TouchesBegan(std::vector<Touch> touches);
  virtual void TouchesMoved(std::vector<Touch> touches);
  virtual void TouchesEnded(std::vector<Touch> touches);
  virtual void ClearTouches();
  virtual void HandleMouseDelta(float delta_x, float delta_y);
  virtual bool HandleBackButton();  // If this returns false, the app is quit.
  virtual void HandlePauseButton() {}
  // If you add an entity using this method, then this EngineView is responsible for releasing this
  // object.
  void AddEntity(ViewEntity *entity);
  void AddEntity(sp<ViewEntity> entity);
  void InsertEntityBefore(ViewEntity *entity, ViewEntity *existing_entity);
  void InsertEntityBefore(sp<ViewEntity> entity, ViewEntity *existing_entity);
  void InsertEntityAfter(ViewEntity *entity, ViewEntity *existing_entity);
  void InsertEntityAfter(sp<ViewEntity> entity, ViewEntity *existing_entity);
  void RemoveEntity(sp<ViewEntity> entity);

  GameEngine *game_engine() { return game_engine_; }
  bool is_visible() { return is_visible_; }

 private:
  void set_is_visible(bool is_visible) { is_visible_ = is_visible; }
  friend class GameEngine;

  GameEngine *game_engine_;  // weak
  std::vector<sp<ViewEntity> > entities_;
  bool is_visible_;
};

#endif
