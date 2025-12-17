#ifndef _ACTION_TRUTH_TABLE_H
#define _ACTION_TRUTH_TABLE_H

#include "Action.h"
#include <vector>

class ApplicationManager;
class Component;

// Action for generating truth table
// Tests all input combinations and shows outputs
class ActionTruthTable : public Action {
public:
  ActionTruthTable(ApplicationManager *pApp);

  virtual void ReadActionParameters();
  virtual void Execute();
  virtual void Undo();
  virtual void Redo();

private:
  // Helper to find all switches and LEDs
  void FindInputsOutputs(std::vector<Component *> &switches,
                         std::vector<Component *> &leds);

  // Helper to run simulation with current switch states
  void SimulateCircuit();
};

#endif
