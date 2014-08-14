//
//  input_module.h
//  GameEngine
//
//  Created by Jon Sharkey on 2012-08-11.
//  Copyright 2012 Sharkable. All rights reserved.
//

#ifndef GAMEENGINE_INPUTMODULE_H_
#define GAMEENGINE_INPUTMODULE_H_

#include "gameengine/module.h"
#include "gameengine/simulation/simulator.h"

class InputModule : public Module, Simulator {
 public:
  virtual void HidePointer() {};
  virtual void ShowPointer() {};
  virtual void TurnOnRotationUpdates() {};
  virtual void TurnOffRotationUpdates() {};
  virtual float device_angle() { return 0.f; }

  // Simulator
  virtual void SimulateStep() {}
};

#endif
