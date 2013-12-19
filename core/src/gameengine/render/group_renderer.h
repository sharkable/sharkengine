//
//  group_renderer.h
//  GameEngine
//
//  Created by Jon Sharkey on 2013-12-08.
//  Copyright 2013 Sharkable. All rights reserved.
//

#ifndef GAMEENGINE_RENDER_SORTEDRENDERER_H_
#define GAMEENGINE_RENDER_SORTEDRENDERER_H_

#include "gameengine/datastructures/staged_vector.h"

#include "gameengine/render/renderer.h"

class GroupRenderer : public Renderer {
 public:
  void AddRenderer(Renderer *renderer) {
    renderers_.StagePushBack(renderer);
  }

  void RemoveRenderer(Renderer *renderer) {
    renderers_.StageErase(renderer);
  }

  // Renderer
  virtual void Render(CoordinateSystem const &coordinate_system) {
    renderers_.CommitStaging();
    for (auto i = renderers_.Begin(); i != renderers_.End(); ++i) {
      (*i)->Render(coordinate_system);
    }
  }

 private:
  StagedVector<Renderer> renderers_;
};

#endif
