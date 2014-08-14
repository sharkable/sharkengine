//
//  simulator.h
//  SharkEngine
//
//  Created by Jon Sharkey on 2013-12-05.
//  Copyright 2013 Sharkable. All rights reserved.
//

#ifndef GAMEENGINE_SIMULATION_SIMULATOR_H_
#define GAMEENGINE_SIMULATION_SIMULATOR_H_

class Simulator {
 public:
  virtual ~Simulator() {}
  virtual void SimulateStep() = 0;
};

#endif
