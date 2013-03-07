//
//  engine_view.h
//  AirHockey
//
//  Created by Jonathan Sharkey on 10-04-10.
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
  EngineView(sp<GameEngine> game_engine);

  virtual void ViewIsShown() {}
  virtual void Update();
  virtual void Render();
  virtual void TouchesBegan(std::vector<Touch> touches);
  virtual void TouchesMoved(std::vector<Touch> touches);
  virtual void TouchesEnded(std::vector<Touch> touches);
  virtual void ClearTouches();
  // If you add an entity using this method, then this EngineView is responsible for releasing this
  // object.
  void AddEntity(ViewEntity *entity);
  void AddEntity(sp<ViewEntity> entity);
  void RemoveEntity(sp<ViewEntity> entity);
  
  sp<GameEngine> game_engine() { return game_engine_; }

 protected:

 private:
  sp<GameEngine> game_engine_;
  std::vector<sp<ViewEntity> > entities_;
};

#endif
