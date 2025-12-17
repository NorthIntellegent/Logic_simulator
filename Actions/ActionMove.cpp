#include "ActionMove.h"
#include "..\ApplicationManager.h"
#include "..\Components\Component.h"
#include "..\Components\Connection.h"
#include "..\GUI\Input.h"
#include "..\GUI\Output.h"

ActionMove::ActionMove(ApplicationManager *pApp) : Action(pApp) {
  m_pSelectedComp = NULL;
  m_OldX = m_OldY = 0;
  m_NewX = m_NewY = 0;
}

void ActionMove::ReadActionParameters() {
  Output *pOut = pManager->GetOutput();
  Input *pIn = pManager->GetInput();

  pOut->PrintMsg("Click on the component to move");
  int x, y;
  pIn->GetPointClicked(x, y);

  m_pSelectedComp = pManager->GetComponentByPosition(x, y);

  if (m_pSelectedComp == NULL) {
    pOut->PrintMsg("No component found at this position!");
    return;
  }

  // Don't allow moving connections directly
  if (dynamic_cast<Connection *>(m_pSelectedComp)) {
    pOut->PrintMsg("Cannot move connections directly. Move the connected "
                   "components instead.");
    m_pSelectedComp = NULL;
    return;
  }

  // Store old position
  GraphicsInfo gfx = m_pSelectedComp->GetGraphicsInfo();
  m_OldX = gfx.x1;
  m_OldY = gfx.y1;

  pOut->PrintMsg("Click on the new position");
  pIn->GetPointClicked(m_NewX, m_NewY);

  pOut->ClearStatusBar();
}

void ActionMove::Execute() {
  Output *pOut = pManager->GetOutput();
  Input *pIn = pManager->GetInput();

  // Check if there are multiple selected components
  int selectedCount = pManager->GetSelectedCount();

  if (selectedCount > 1) {
    // Multi-move: ask for offset
    pOut->PrintMsg("Multi-move: Click on reference point, then destination");
    int refX, refY;
    pIn->GetPointClicked(refX, refY);

    pOut->PrintMsg("Click on destination");
    int destX, destY;
    pIn->GetPointClicked(destX, destY);

    int dx = destX - refX;
    int dy = destY - refY;

    pManager->MoveAllSelected(dx, dy);
    pManager->UpdateInterface();
    pOut->PrintMsg("Moved " + to_string(selectedCount) + " components");
    return;
  }

  // Single component move
  ReadActionParameters();

  if (m_pSelectedComp == NULL)
    return;

  // Calculate the offset
  int dx = m_NewX - m_OldX;
  int dy = m_NewY - m_OldY;

  // Get current graphics info
  GraphicsInfo gfx = m_pSelectedComp->GetGraphicsInfo();

  // Calculate new position
  GraphicsInfo newGfx;
  newGfx.x1 = gfx.x1 + dx;
  newGfx.y1 = gfx.y1 + dy;
  newGfx.x2 = gfx.x2 + dx;
  newGfx.y2 = gfx.y2 + dy;

  // Check bounds (don't move above toolbar or below status bar)
  if (newGfx.y1 < UI.ToolBarHeight) {
    pOut->PrintMsg("Cannot move component into toolbar area!");
    return;
  }

  // Update component position
  m_pSelectedComp->SetGraphicsInfo(newGfx);

  // Update the interface
  pManager->UpdateInterface();

  pOut->PrintMsg("Component moved successfully!");
}

void ActionMove::Undo() {
  if (m_pSelectedComp == NULL)
    return;

  // Restore old position
  GraphicsInfo gfx = m_pSelectedComp->GetGraphicsInfo();
  int dx = m_OldX - gfx.x1;
  int dy = m_OldY - gfx.y1;

  GraphicsInfo newGfx;
  newGfx.x1 = gfx.x1 + dx;
  newGfx.y1 = gfx.y1 + dy;
  newGfx.x2 = gfx.x2 + dx;
  newGfx.y2 = gfx.y2 + dy;

  m_pSelectedComp->SetGraphicsInfo(newGfx);
  pManager->UpdateInterface();
}

void ActionMove::Redo() {
  if (m_pSelectedComp == NULL)
    return;

  // Move to new position again
  int dx = m_NewX - m_OldX;
  int dy = m_NewY - m_OldY;

  GraphicsInfo gfx = m_pSelectedComp->GetGraphicsInfo();
  GraphicsInfo newGfx;
  newGfx.x1 = gfx.x1 + dx;
  newGfx.y1 = gfx.y1 + dy;
  newGfx.x2 = gfx.x2 + dx;
  newGfx.y2 = gfx.y2 + dy;

  m_pSelectedComp->SetGraphicsInfo(newGfx);
  pManager->UpdateInterface();
}
