#ifndef _ACTION_SIMULATE_H
#define _ACTION_SIMULATE_H

#include "Action.h"

class ApplicationManager;

// Action for running circuit simulation
// Propagates signals from switches through gates to LEDs
class ActionSimulate : public Action {
public:
  ActionSimulate(ApplicationManager *pApp);

  virtual void ReadActionParameters();
  virtual void Execute();
  virtual void Undo();
  virtual void Redo();

private:
  // Helper to validate circuit before simulation
  bool ValidateCircuit();

  // Helper to propagate signals through the circuit
  void PropagateSignals();
};

#endif
