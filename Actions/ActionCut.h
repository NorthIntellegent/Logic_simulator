#ifndef _ACTION_CUT_H
#define _ACTION_CUT_H

#include "Action.h"

class ApplicationManager;
class Component;

// Action for cutting components (removes from circuit, stores in clipboard)
class ActionCut : public Action {
private:
  Component *m_pCutComp; // Cut component (for undo)

public:
  ActionCut(ApplicationManager *pApp);

  virtual void ReadActionParameters();
  virtual void Execute();
  virtual void Undo();
  virtual void Redo();
};

#endif
