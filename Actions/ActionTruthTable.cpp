#include "ActionTruthTable.h"
#include "..\ApplicationManager.h"
#include "..\Components\Component.h"
#include "..\Components\Connection.h"
#include "..\Components\Gate.h"
#include "..\Components\LED.h"
#include "..\Components\SWITCH.h"
#include "..\GUI\Input.h"
#include "..\GUI\Output.h"
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>


using namespace std;

ActionTruthTable::ActionTruthTable(ApplicationManager *pApp) : Action(pApp) {}

void ActionTruthTable::ReadActionParameters() {
  // No parameters needed
}

void ActionTruthTable::FindInputsOutputs(vector<Component *> &switches,
                                         vector<Component *> &leds) {
  int compCount = pManager->GetComponentCount();

  for (int i = 0; i < compCount; i++) {
    Component *pComp = pManager->GetComponent(i);
    if (pComp) {
      if (dynamic_cast<SWITCH *>(pComp))
        switches.push_back(pComp);
      else if (dynamic_cast<LED *>(pComp))
        leds.push_back(pComp);
    }
  }
}

void ActionTruthTable::SimulateCircuit() {
  int compCount = pManager->GetComponentCount();

  // Multiple passes to ensure all signals propagate
  for (int pass = 0; pass < 10; pass++) {
    // Operate switches
    for (int i = 0; i < compCount; i++) {
      Component *pComp = pManager->GetComponent(i);
      SWITCH *pSwitch = dynamic_cast<SWITCH *>(pComp);
      if (pSwitch)
        pSwitch->Operate();
    }

    // Operate connections
    for (int i = 0; i < compCount; i++) {
      Component *pComp = pManager->GetComponent(i);
      Connection *pConn = dynamic_cast<Connection *>(pComp);
      if (pConn)
        pConn->Operate();
    }

    // Operate gates
    for (int i = 0; i < compCount; i++) {
      Component *pComp = pManager->GetComponent(i);
      Gate *pGate = dynamic_cast<Gate *>(pComp);
      if (pGate)
        pGate->Operate();
    }

    // Operate LEDs
    for (int i = 0; i < compCount; i++) {
      Component *pComp = pManager->GetComponent(i);
      LED *pLED = dynamic_cast<LED *>(pComp);
      if (pLED)
        pLED->Operate();
    }
  }
}

void ActionTruthTable::Execute() {
  ReadActionParameters();

  Output *pOut = pManager->GetOutput();

  // Find all switches (inputs) and LEDs (outputs)
  vector<Component *> switches;
  vector<Component *> leds;
  FindInputsOutputs(switches, leds);

  int numInputs = switches.size();
  int numOutputs = leds.size();

  if (numInputs == 0) {
    pOut->PrintMsg("Error: No switches found in the circuit!");
    return;
  }

  if (numOutputs == 0) {
    pOut->PrintMsg("Error: No LEDs found in the circuit!");
    return;
  }

  if (numInputs > 8) {
    pOut->PrintMsg("Warning: Too many inputs! Maximum 8 switches supported.");
    return;
  }

  // Calculate number of rows (2^numInputs)
  int numRows = (int)pow(2.0, numInputs);

  // Print header to console
  cout << "\n===== TRUTH TABLE =====\n";

  // Print header row
  for (int i = 0; i < numInputs; i++) {
    string label = switches[i]->GetLabel();
    if (label.empty() || label == "$")
      cout << "SW" << (i + 1) << "\t";
    else
      cout << label << "\t";
  }
  cout << "|\t";
  for (int i = 0; i < numOutputs; i++) {
    string label = leds[i]->GetLabel();
    if (label.empty() || label == "$")
      cout << "LED" << (i + 1) << "\t";
    else
      cout << label << "\t";
  }
  cout << endl;

  // Print separator
  for (int i = 0; i < numInputs + numOutputs + 1; i++)
    cout << "----\t";
  cout << endl;

  // Generate truth table
  for (int row = 0; row < numRows; row++) {
    // Set switch states based on row number
    for (int i = 0; i < numInputs; i++) {
      SWITCH *pSwitch = dynamic_cast<SWITCH *>(switches[i]);
      if (pSwitch) {
        // Check bit i of row
        int bitVal = (row >> i) & 1;
        pSwitch->SetStatus(bitVal ? HIGH : LOW);
      }
    }

    // Run simulation
    SimulateCircuit();

    // Print input values
    for (int i = 0; i < numInputs; i++) {
      SWITCH *pSwitch = dynamic_cast<SWITCH *>(switches[i]);
      cout << (pSwitch->GetStatus() == HIGH ? "1" : "0") << "\t";
    }
    cout << "|\t";

    // Print output values
    for (int i = 0; i < numOutputs; i++) {
      LED *pLED = dynamic_cast<LED *>(leds[i]);
      int status = pLED->GetInputPinStatus(1);
      cout << (status == HIGH ? "1" : "0") << "\t";
    }
    cout << endl;
  }

  cout << "=======================\n" << endl;

  pOut->PrintMsg("Truth table generated! Check the console window.");

  // Restore original switch states (all LOW)
  for (int i = 0; i < numInputs; i++) {
    SWITCH *pSwitch = dynamic_cast<SWITCH *>(switches[i]);
    if (pSwitch)
      pSwitch->SetStatus(LOW);
  }
}

void ActionTruthTable::Undo() {
  // Truth table generation doesn't need undo
}

void ActionTruthTable::Redo() {
  // Truth table generation doesn't need redo
}
