//
//  input_module.h
//  SharkEngine
//
//  Created by Jon Sharkey on 2012-08-11.
//  Copyright 2012 Sharkable. All rights reserved.
//

#ifndef SHARKENGINE_INPUTMODULE_H_
#define SHARKENGINE_INPUTMODULE_H_

#include "sharkengine/module.h"
#include "sharkengine/simulation/simulator.h"

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
