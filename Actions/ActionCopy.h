#ifndef _ACTION_COPY_H
#define _ACTION_COPY_H

#include "Action.h"

class ApplicationManager;
class Component;

// Action for copying components (without connections)
class ActionCopy : public Action {
public:
  ActionCopy(ApplicationManager *pApp);

  virtual void ReadActionParameters();
  virtual void Execute();
  virtual void Undo();
  virtual void Redo();
};

#endif
