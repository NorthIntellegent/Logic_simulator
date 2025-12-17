#ifndef _ACTION_CHANGE_SWITCH_H
#define _ACTION_CHANGE_SWITCH_H

#include "Action.h"

class ApplicationManager;
class Component;

// Action for toggling switch state in simulation mode
class ActionChangeSwitch : public Action {
private:
  int m_ClickX, m_ClickY;       // Click coordinates
  Component *m_pSelectedSwitch; // Selected switch component

  // Helper function to find switch at coordinates
  Component *FindSwitchAt(int x, int y);

  // Helper function to run simulation after switch toggle
  void RunSimulation();

public:
  ActionChangeSwitch(ApplicationManager *pApp);

  virtual void ReadActionParameters();
  virtual void Execute();
  virtual void Undo();
  virtual void Redo();
};

#endif
