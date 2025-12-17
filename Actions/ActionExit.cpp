#include "ActionExit.h"
#include "..\ApplicationManager.h"
#include "..\GUI\Input.h"
#include "..\GUI\Output.h"
#include <cstdlib>


ActionExit::ActionExit(ApplicationManager *pApp) : Action(pApp) {}

void ActionExit::ReadActionParameters() {
  // No parameters needed
}

void ActionExit::Execute() {
  Output *pOut = pManager->GetOutput();
  Input *pIn = pManager->GetInput();

  pOut->PrintMsg("Are you sure you want to exit? (y/n)");
  string response = pIn->GetString(pOut);

  if (response == "y" || response == "Y" || response == "yes" ||
      response == "Yes") {
    pOut->PrintMsg("Exiting application...");
    exit(0); // Exit the application
  } else {
    pOut->PrintMsg("Exit cancelled.");
  }
}

void ActionExit::Undo() {
  // Cannot undo exit
}

void ActionExit::Redo() {
  // Cannot redo exit
}
