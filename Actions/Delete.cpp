#include "Delete.h"
#include "..\ApplicationManager.h"

Delete::Delete(ApplicationManager *pApp) : Action(pApp) { pComp = NULL; }

Delete::~Delete() {}

void Delete::ReadActionParameters() {
  // Get a Pointer to the Input / Output Interfaces
  Output *pOut = pManager->GetOutput();
  Input *pIn = pManager->GetInput();

  // Print Action Message
  pOut->PrintMsg("Delete: Click on a component to delete");

  // Wait for User to click on component
  pIn->GetPointClicked(Cx, Cy);

  // Get the component at this position
  pComp = pManager->GetComponentByPosition(Cx, Cy);

  if (!pComp) {
    pOut->PrintMsg("No component found at this position");
  }

  // Clear Status Bar
  pOut->ClearStatusBar();
}

void Delete::Execute() {
  Output *pOut = pManager->GetOutput();

  // Check if there are multiple selected components
  int selectedCount = pManager->GetSelectedCount();

  if (selectedCount > 1) {
    // Delete all selected components
    pOut->PrintMsg("Deleting all selected components...");
    pManager->DeleteAllSelected();
    pManager->UpdateInterface();
    pOut->PrintMsg("Deleted " + to_string(selectedCount) + " components");
    return;
  }

  // Get parameters (click on single component)
  ReadActionParameters();

  // Delete the component if found
  if (pComp) {
    pManager->DeleteComponent(pComp);
    pManager->UpdateInterface();
    pOut->PrintMsg("Component deleted");
  }
}

void Delete::Undo() {
  // For Undo, we would need to restore the component
  // This requires storing the component data
  // For now, leave unimplemented
}

void Delete::Redo() {
  // For Redo, delete again
  // For now, leave unimplemented
}
