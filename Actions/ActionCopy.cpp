#include "ActionCopy.h"
#include "..\ApplicationManager.h"
#include "..\Components\Component.h"
#include "..\Components\Connection.h"
#include "..\GUI\Input.h"
#include "..\GUI\Output.h"

ActionCopy::ActionCopy(ApplicationManager *pApp) : Action(pApp) {}

void ActionCopy::ReadActionParameters() {
  Output *pOut = pManager->GetOutput();
  Input *pIn = pManager->GetInput();

  pOut->PrintMsg("Click on the component to copy");
  int x, y;
  pIn->GetPointClicked(x, y);

  Component *pComp = pManager->GetComponentByPosition(x, y);

  if (pComp == NULL) {
    pOut->PrintMsg("No component found at this position!");
    return;
  }

  // Don't allow copying connections
  if (dynamic_cast<Connection *>(pComp)) {
    pOut->PrintMsg("Cannot copy connections. Copy the components instead.");
    return;
  }

  // Store type name in clipboard
  pManager->SetClipboard(pComp->GetTypeName());
  pOut->PrintMsg("Component copied to clipboard!");
}

void ActionCopy::Execute() { ReadActionParameters(); }

void ActionCopy::Undo() {
  // Copy doesn't need undo
}

void ActionCopy::Redo() {
  // Copy doesn't need redo
}
