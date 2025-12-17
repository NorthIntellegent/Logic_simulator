#ifndef _ACTION_PASTE_H
#define _ACTION_PASTE_H

#include "Action.h"

class ApplicationManager;
class Component;

// Action for pasting components from clipboard
class ActionPaste : public Action {
private:
  Component *m_pPastedComp; // New pasted component
  int m_PasteX, m_PasteY;   // Paste position

public:
  ActionPaste(ApplicationManager *pApp);

  virtual void ReadActionParameters();
  virtual void Execute();
  virtual void Undo();
  virtual void Redo();
};

#endif
