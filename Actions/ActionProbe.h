#ifndef _ACTION_PROBE_H
#define _ACTION_PROBE_H

#include "Action.h"

class ApplicationManager;
class Component;

// Action for probing circuit components and connections
// Displays the current HIGH/LOW status of clicked component or connection
class ActionProbe : public Action {
private:
  int m_ClickX, m_ClickY;     // Click coordinates
  Component *m_pSelectedComp; // Selected component to probe

public:
  ActionProbe(ApplicationManager *pApp);

  // Read click position from user
  virtual void ReadActionParameters();

  // Execute probe action - find component and display status
  virtual void Execute();

  virtual void Undo(); // Probing doesn't need undo
  virtual void Redo(); // Probing doesn't need redo
};

#endif
