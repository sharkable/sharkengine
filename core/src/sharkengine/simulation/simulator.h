//
//  simulator.h
//  SharkEngine
//
//  Created by Jon Sharkey on 2013-12-05.
//  Copyright 2013 Sharkable. All rights reserved.
//

#ifndef SHARKENGINE_SIMULATION_SIMULATOR_H_
#define SHARKENGINE_SIMULATION_SIMULATOR_H_

class Simulator {
 public:
  virtual ~Simulator() {}
  virtual void SimulateStep() = 0;
};

#endif
