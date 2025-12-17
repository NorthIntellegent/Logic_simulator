#include "ActionSimulate.h"
#include "..\ApplicationManager.h"
#include "..\Components\Component.h"
#include "..\Components\Connection.h"
#include "..\Components\Gate.h"
#include "..\Components\LED.h"
#include "..\Components\SWITCH.h"
#include "..\GUI\Input.h"
#include "..\GUI\Output.h"

ActionSimulate::ActionSimulate(ApplicationManager *pApp) : Action(pApp) {}

void ActionSimulate::ReadActionParameters() {
  // No parameters needed for simulation
}

void ActionSimulate::Execute() {
  ReadActionParameters();

  Output *pOut = pManager->GetOutput();

  // First, validate the circuit
  pOut->PrintMsg("Validating circuit...");

  bool isValid = ValidateCircuit();

  if (!isValid) {
    pOut->PrintMsg("Circuit validation FAILED! Check for unconnected pins.");
    return;
  }

  pOut->PrintMsg("Circuit is valid! Running simulation...");

  // Propagate signals through the circuit
  PropagateSignals();

  // Redraw everything to show new states
  pManager->UpdateInterface();

  pOut->PrintMsg("Simulation complete! Circuit is valid.");
}

bool ActionSimulate::ValidateCircuit() {
  int compCount = pManager->GetComponentCount();
  int errors = 0;

  for (int i = 0; i < compCount; i++) {
    Component *pComp = pManager->GetComponent(i);
    if (!pComp)
      continue;

    // Skip connections in validation
    if (dynamic_cast<Connection *>(pComp))
      continue;

    // Check gates for unconnected input pins
    Gate *pGate = dynamic_cast<Gate *>(pComp);
    if (pGate) {
      // Check each input pin
      for (int pin = 1; pin <= 3; pin++) { // Max 3 inputs
        InputPin *pInput = pGate->GetInputPin(pin - 1);
        if (pInput && !pInput->isConnected()) {
          // This input exists but is not connected
          // For now, we'll be lenient and just count errors
          errors++;
        }
      }
    }

    // Check switches - should have at least one outgoing connection
    SWITCH *pSwitch = dynamic_cast<SWITCH *>(pComp);
    if (pSwitch) {
      OutputPin *pOutput = pSwitch->GetOutputPin();
      if (pOutput && pOutput->getConnectionCount() == 0) {
        errors++; // Switch output not connected
      }
    }

    // Check LEDs - input should be connected
    LED *pLED = dynamic_cast<LED *>(pComp);
    if (pLED) {
      InputPin *pInput = pLED->GetInputPin();
      if (pInput && !pInput->isConnected()) {
        errors++; // LED input not connected
      }
    }
  }

  // For now, allow circuits with some unconnected pins
  // but warn the user
  return (errors == 0);
}

void ActionSimulate::PropagateSignals() {
  int compCount = pManager->GetComponentCount();

  // Multiple passes to ensure all signals propagate
  // (handles cascaded gates)
  for (int pass = 0; pass < 10; pass++) {
    // Step 1: Operate all switches to set their output pins
    for (int i = 0; i < compCount; i++) {
      Component *pComp = pManager->GetComponent(i);
      if (pComp) {
        SWITCH *pSwitch = dynamic_cast<SWITCH *>(pComp);
        if (pSwitch) {
          pSwitch->Operate();
        }
      }
    }

    // Step 2: Operate all connections to propagate switch outputs
    for (int i = 0; i < compCount; i++) {
      Component *pComp = pManager->GetComponent(i);
      if (pComp) {
        Connection *pConn = dynamic_cast<Connection *>(pComp);
        if (pConn) {
          pConn->Operate();
        }
      }
    }

    // Step 3: Operate all gates to compute their outputs
    for (int i = 0; i < compCount; i++) {
      Component *pComp = pManager->GetComponent(i);
      if (pComp) {
        Gate *pGate = dynamic_cast<Gate *>(pComp);
        if (pGate) {
          pGate->Operate();
        }
      }
    }

    // Step 4: Operate connections AGAIN to propagate gate outputs to LEDs
    for (int i = 0; i < compCount; i++) {
      Component *pComp = pManager->GetComponent(i);
      if (pComp) {
        Connection *pConn = dynamic_cast<Connection *>(pComp);
        if (pConn) {
          pConn->Operate();
        }
      }
    }

    // Step 5: LEDs will be updated when drawn - no Operate needed
  }
}

void ActionSimulate::Undo() {
  // Simulation doesn't need undo
}

void ActionSimulate::Redo() {
  // Simulation doesn't need redo
}
