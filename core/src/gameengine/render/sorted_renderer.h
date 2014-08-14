//
//  sorted_renderer.h
//  SharkEngine
//
//  Created by Jon Sharkey on 2013-12-08.
//  Copyright 2013 Sharkable. All rights reserved.
//

#ifndef SHARKENGINE_RENDER_SORTEDRENDERER_H_
#define SHARKENGINE_RENDER_SORTEDRENDERER_H_

#include "gameengine/datastructures/staged_vector.h"

#include "gameengine/render/renderer.h"

static bool CompareRenderersByPointer(Renderer *a, Renderer *b) {
  return a->SortValue() <= b->SortValue();
}

class SortedRenderer : public Renderer {
 public:
  void AddRenderer(Renderer *renderer) {
    renderers_.StageOrderedInsert(renderer, CompareRenderersByPointer);
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
