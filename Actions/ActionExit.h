#ifndef _ACTION_EXIT_H
#define _ACTION_EXIT_H

#include "Action.h"

class ApplicationManager;

// Action for exiting the application
class ActionExit : public Action {
public:
  ActionExit(ApplicationManager *pApp);

  virtual void ReadActionParameters();
  virtual void Execute();
  virtual void Undo();
  virtual void Redo();
};

#endif
