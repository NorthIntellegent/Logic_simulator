#include "ActionChangeSwitch.h"
#include "..\ApplicationManager.h"
#include "..\Components\Component.h"
#include "..\Components\Connection.h"
#include "..\Components\Gate.h"
#include "..\Components\LED.h"
#include "..\Components\SWITCH.h"
#include "..\GUI\Input.h"
#include "..\GUI\Output.h"

ActionChangeSwitch::ActionChangeSwitch(ApplicationManager *pApp)
    : Action(pApp) {
  m_pSelectedSwitch = NULL;
  m_ClickX = 0;
  m_ClickY = 0;
}

void ActionChangeSwitch::ReadActionParameters() {
  Output *pOut = pManager->GetOutput();
  Input *pIn = pManager->GetInput();

  pOut->PrintMsg("Click on a switch to toggle it (ON/OFF)");
  pIn->GetPointClicked(m_ClickX, m_ClickY);
  pOut->ClearStatusBar();
}

void ActionChangeSwitch::Execute() {
  ReadActionParameters();
  m_pSelectedSwitch = FindSwitchAt(m_ClickX, m_ClickY);

  if (m_pSelectedSwitch == NULL) {
    pManager->GetOutput()->PrintMsg("No switch found at this location!");
    return;
  }

  SWITCH *pSwitch = dynamic_cast<SWITCH *>(m_pSelectedSwitch);
  if (pSwitch) {
    pSwitch->Toggle();

    string statusMsg = "Switch toggled to ";
    statusMsg += (pSwitch->GetStatus() == HIGH) ? "ON" : "OFF";
    pManager->GetOutput()->PrintMsg(statusMsg);

    // Run simulation to propagate signals through the circuit
    RunSimulation();

    // Update interface to show new state
    pManager->UpdateInterface();
  } else {
    pManager->GetOutput()->PrintMsg("Selected component is not a switch!");
  }
}

void ActionChangeSwitch::RunSimulation() {
  int compCount = pManager->GetComponentCount();

  // Multiple passes to ensure all signals propagate through cascaded gates
  for (int pass = 0; pass < 10; pass++) {
    // Step 1: Operate all switches to set their output pins
    for (int i = 0; i < compCount; i++) {
      Component *pComp = pManager->GetComponent(i);
      SWITCH *pSw = dynamic_cast<SWITCH *>(pComp);
      if (pSw)
        pSw->Operate();
    }

    // Step 2: Operate all connections to propagate switch outputs to gate
    // inputs
    for (int i = 0; i < compCount; i++) {
      Component *pComp = pManager->GetComponent(i);
      Connection *pConn = dynamic_cast<Connection *>(pComp);
      if (pConn)
        pConn->Operate();
    }

    // Step 3: Operate all gates to compute their outputs
    for (int i = 0; i < compCount; i++) {
      Component *pComp = pManager->GetComponent(i);
      Gate *pGate = dynamic_cast<Gate *>(pComp);
      if (pGate)
        pGate->Operate();
    }

    // Step 4: Operate connections AGAIN to propagate gate outputs to LEDs/next
    // gates
    for (int i = 0; i < compCount; i++) {
      Component *pComp = pManager->GetComponent(i);
      Connection *pConn = dynamic_cast<Connection *>(pComp);
      if (pConn)
        pConn->Operate();
    }

    // Step 5: LEDs just need to be redrawn (their input is already set)
    // No Operate() needed - Draw() will check input pin status
  }
}

Component *ActionChangeSwitch::FindSwitchAt(int x, int y) {
  Component *pComp = pManager->GetComponentByPosition(x, y);

  if (pComp && dynamic_cast<SWITCH *>(pComp)) {
    return pComp;
  }

  return NULL;
}

void ActionChangeSwitch::Undo() {
  if (m_pSelectedSwitch != NULL) {
    SWITCH *pSwitch = dynamic_cast<SWITCH *>(m_pSelectedSwitch);
    if (pSwitch) {
      pSwitch->Toggle();
      pManager->UpdateInterface();
    }
  }
}

void ActionChangeSwitch::Redo() {
  if (m_pSelectedSwitch != NULL) {
    SWITCH *pSwitch = dynamic_cast<SWITCH *>(m_pSelectedSwitch);
    if (pSwitch) {
      pSwitch->Toggle();
      pManager->UpdateInterface();
    }
  }
}
