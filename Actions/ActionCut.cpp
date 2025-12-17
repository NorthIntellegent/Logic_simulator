#include "ActionCut.h"
#include "..\ApplicationManager.h"
#include "..\Components\Component.h"
#include "..\Components\Connection.h"
#include "..\GUI\Input.h"
#include "..\GUI\Output.h"

ActionCut::ActionCut(ApplicationManager *pApp) : Action(pApp) {
  m_pCutComp = NULL;
}

void ActionCut::ReadActionParameters() {
  Output *pOut = pManager->GetOutput();
  Input *pIn = pManager->GetInput();

  pOut->PrintMsg("Click on the component to cut");
  int x, y;
  pIn->GetPointClicked(x, y);

  m_pCutComp = pManager->GetComponentByPosition(x, y);

  if (m_pCutComp == NULL) {
    pOut->PrintMsg("No component found at this position!");
    return;
  }

  // Don't allow cutting connections directly
  if (dynamic_cast<Connection *>(m_pCutComp)) {
    pOut->PrintMsg("Cannot cut connections. Cut the components instead.");
    m_pCutComp = NULL;
    return;
  }

  pOut->ClearStatusBar();
}

void ActionCut::Execute() {
  ReadActionParameters();

  if (m_pCutComp == NULL)
    return;

  Output *pOut = pManager->GetOutput();

  // Store type name in clipboard (before deleting!)
  pManager->SetClipboard(m_pCutComp->GetTypeName());

  // Delete the component (and its connections)
  pManager->DeleteComponent(m_pCutComp);

  pManager->UpdateInterface();
  pOut->PrintMsg("Component cut to clipboard!");
}

void ActionCut::Undo() {
  // Would need to restore component - complex, skip for now
}

void ActionCut::Redo() {
  // Would need to delete component again - complex, skip for now
}
