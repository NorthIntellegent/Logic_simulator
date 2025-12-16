#ifndef _ADD_CONNECTION_H
#define _ADD_CONNECTION_H

#include "..\Components\Connection.h"
#include "action.h"

class AddConnection : public Action {
private:
  Component *pSrcComp; // Source component (clicked first)
  Component *pDstComp; // Destination component (clicked second)
  int DstPinIndex;     // Which input pin on destination (0-based)
  int SrcX, SrcY;      // Click position on source component
  int DstX, DstY;      // Click position on destination component
public:
  AddConnection(ApplicationManager *pApp);
  virtual ~AddConnection(void);

  // Reads parameters required for action to execute
  virtual void ReadActionParameters();
  // Execute action (code depends on action type)
  virtual void Execute();

  virtual void Undo();
  virtual void Redo();
};

#endif
