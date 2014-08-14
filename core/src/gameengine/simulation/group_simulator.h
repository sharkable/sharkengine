//
//  group_simulator.h
//  SharkEngine
//
//  Created by Jon Sharkey on 2013-12-29.
//  Copyright 2013 Sharkable. All rights reserved.
//

#ifndef GAMEENGINE_SIMULATION_GROUPSIMULATOR_H_
#define GAMEENGINE_SIMULATION_GROUPSIMULATOR_H_

#include "gameengine/datastructures/staged_vector.h"

#include "gameengine/simulation/simulator.h"

class GroupSimulator : public Simulator {
 public:
  void AddSimulator(Simulator *simulator) {
    simulators_.StagePushBack(simulator);
  }

  void RemoveSimulator(Simulator *simulator) {
    simulators_.StageErase(simulator);
  }

  // Simulator
  virtual void SimulateStep() {
    simulators_.CommitStaging();
    for (auto i = simulators_.Begin(); i != simulators_.End(); ++i) {
      (*i)->SimulateStep();
    }
  }

 private:
  StagedVector<Simulator> simulators_;
};

#endif
