#ifndef _ACTION_MOVE_H
#define _ACTION_MOVE_H

#include "Action.h"

class ApplicationManager;
class Component;

// Action for moving components
class ActionMove : public Action {
private:
  Component *m_pSelectedComp; // Component to move
  int m_OldX, m_OldY;         // Original position
  int m_NewX, m_NewY;         // New position

public:
  ActionMove(ApplicationManager *pApp);

  virtual void ReadActionParameters();
  virtual void Execute();
  virtual void Undo();
  virtual void Redo();
};

#endif
