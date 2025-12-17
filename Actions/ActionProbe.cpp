#include "ActionProbe.h"
#include "..\ApplicationManager.h"
#include "..\Components\Component.h"
#include "..\Components\Connection.h"
#include "..\Components\Gate.h"
#include "..\Components\LED.h"
#include "..\Components\SWITCH.h"
#include "..\GUI\Input.h"
#include "..\GUI\Output.h"


ActionProbe::ActionProbe(ApplicationManager *pApp) : Action(pApp) {
  m_pSelectedComp = NULL;
  m_ClickX = 0;
  m_ClickY = 0;
}

void ActionProbe::ReadActionParameters() {
  Output *pOut = pManager->GetOutput();
  Input *pIn = pManager->GetInput();

  pOut->PrintMsg("Click on a component or connection to probe its value");
  pIn->GetPointClicked(m_ClickX, m_ClickY);
  pOut->ClearStatusBar();
}

void ActionProbe::Execute() {
  ReadActionParameters();

  // Find component at clicked location
  m_pSelectedComp = pManager->GetComponentByPosition(m_ClickX, m_ClickY);

  if (m_pSelectedComp == NULL) {
    pManager->GetOutput()->PrintMsg("No component found at this location!");
    return;
  }

  // Get component info
  string typeName = m_pSelectedComp->GetTypeName();
  string label = m_pSelectedComp->GetLabel();

  // Build message
  string msg = typeName;
  if (!label.empty() && label != "$") {
    msg += " (" + label + ")";
  }

  // Get output status if available
  int outStatus = m_pSelectedComp->GetOutPinStatus();
  if (outStatus != -1) {
    msg += " Output: ";
    msg += (outStatus == HIGH) ? "HIGH (1)" : "LOW (0)";
  } else {
    msg += " - No output pin";
  }

  pManager->GetOutput()->PrintMsg(msg);
}

void ActionProbe::Undo() {
  // Probing doesn't modify the circuit, so no undo needed
}

void ActionProbe::Redo() {
  // Probing doesn't modify the circuit, so no redo needed
}
