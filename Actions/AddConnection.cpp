#include "AddConnection.h"
#include "..\ApplicationManager.h"
#include "..\Components\Gate.h"
#include "..\Components\LED.h"
#include "..\Components\SWITCH.h"

AddConnection::AddConnection(ApplicationManager *pApp) : Action(pApp) {
  pSrcComp = NULL;
  pDstComp = NULL;
  DstPinIndex = 0;
  SrcX = SrcY = DstX = DstY = 0;
}

AddConnection::~AddConnection(void) {}

void AddConnection::ReadActionParameters() {
  // Get a Pointer to the Input / Output Interfaces
  Output *pOut = pManager->GetOutput();
  Input *pIn = pManager->GetInput();

  // Step 1: Get source component
  pOut->PrintMsg("Connection: Click on source component (output)");
  pIn->GetPointClicked(SrcX, SrcY);
  pSrcComp = pManager->GetComponentByPosition(SrcX, SrcY);

  if (!pSrcComp) {
    pOut->PrintMsg("Error: No source component found at that position!");
    return;
  }

  // Step 2: Get destination component
  pOut->PrintMsg("Connection: Click on destination component (input)");
  pIn->GetPointClicked(DstX, DstY);
  pDstComp = pManager->GetComponentByPosition(DstX, DstY);

  if (!pDstComp) {
    pOut->PrintMsg("Error: No destination component found at that position!");
    return;
  }

  // Check if source and destination are the same component (self-connection)
  if (pSrcComp == pDstComp) {
    pOut->PrintMsg("Error: Cannot connect a component to itself!");
    return;
  }

  // Step 3: For multi-input gates, ask for pin number
  Gate *pDstGate = dynamic_cast<Gate *>(pDstComp);
  if (pDstGate) {
    // Check if it's a 3-input gate (AND3, NOR3, XOR3)
    string typeName = pDstComp->GetTypeName();
    if (typeName == "AND3" || typeName == "NOR3" || typeName == "XOR3") {
      pOut->PrintMsg("Enter input pin number (1, 2, or 3):");
      string pinStr = pIn->GetString(pOut);
      if (pinStr == "1")
        DstPinIndex = 0;
      else if (pinStr == "2")
        DstPinIndex = 1;
      else if (pinStr == "3")
        DstPinIndex = 2;
      else
        DstPinIndex = 0; // Default to first pin
    } else if (typeName != "BUFFER" && typeName != "INVERTER") {
      // 2-input gate
      pOut->PrintMsg("Enter input pin number (1 or 2):");
      string pinStr = pIn->GetString(pOut);
      if (pinStr == "2")
        DstPinIndex = 1;
      else
        DstPinIndex = 0;
    } else {
      // Buffer/Inverter - only 1 input
      DstPinIndex = 0;
    }
  } else {
    // LED has only 1 input pin
    DstPinIndex = 0;
  }

  // Clear Status Bar
  pOut->ClearStatusBar();
}

void AddConnection::Execute() {
  // Get parameters (source and destination components)
  ReadActionParameters();

  if (!pSrcComp || !pDstComp) {
    return; // Error occurred in ReadActionParameters
  }

  // Get OutputPin from source component
  OutputPin *pSrcPin = NULL;

  // Check if source is a Gate
  Gate *pSrcGate = dynamic_cast<Gate *>(pSrcComp);
  if (pSrcGate) {
    pSrcPin = pSrcGate->GetOutputPin();
  } else {
    // Check if source is a SWITCH
    SWITCH *pSrcSwitch = dynamic_cast<SWITCH *>(pSrcComp);
    if (pSrcSwitch) {
      pSrcPin = pSrcSwitch->GetOutputPin();
    }
  }

  // Get InputPin from destination component
  InputPin *pDstPin = NULL;

  // Check if destination is a Gate
  Gate *pDstGate = dynamic_cast<Gate *>(pDstComp);
  if (pDstGate) {
    pDstPin = pDstGate->GetInputPin(DstPinIndex);
  } else {
    // Check if destination is an LED
    LED *pDstLED = dynamic_cast<LED *>(pDstComp);
    if (pDstLED) {
      pDstPin = pDstLED->GetInputPin();
    }
  }

  if (!pSrcPin) {
    pManager->GetOutput()->PrintMsg(
        "Error: Source component has no output pin!");
    return;
  }

  if (!pDstPin) {
    pManager->GetOutput()->PrintMsg(
        "Error: Destination component has no input pin!");
    return;
  }

  // Check if source output pin already has a connection
  // (Removed restriction to allow fan-out: one output can connect to multiple
  // inputs)

  // Create GraphicsInfo for the connection
  // Use actual component positions from GetGraphicsInfo()
  GraphicsInfo GInfo;

  // Get actual source component bounds
  GraphicsInfo srcGfx = pSrcComp->GetGraphicsInfo();

  // Connection starts from RIGHT edge of source, middle height
  GInfo.x1 = srcGfx.x2;                   // Right edge
  GInfo.y1 = (srcGfx.y1 + srcGfx.y2) / 2; // Middle height

  // Get actual destination component bounds
  GraphicsInfo dstGfx = pDstComp->GetGraphicsInfo();
  int dstHeight = dstGfx.y2 - dstGfx.y1;

  // Connection ends at LEFT edge of destination
  GInfo.x2 = dstGfx.x1; // Left edge

  // Determine number of inputs for destination gate to position the pin
  // correctly
  string dstTypeName = pDstComp->GetTypeName();
  int numInputs = 1; // Default for LED, Buffer, Inverter

  if (dstTypeName == "AND3" || dstTypeName == "NOR3" || dstTypeName == "XOR3") {
    numInputs = 3;
  } else if (dstTypeName == "AND2" || dstTypeName == "OR2" ||
             dstTypeName == "NAND2" || dstTypeName == "NOR2" ||
             dstTypeName == "XOR2" || dstTypeName == "XNOR2") {
    numInputs = 2;
  }

  // Calculate Y position based on pin index
  // Pins are evenly distributed on the left edge
  if (numInputs == 1) {
    GInfo.y2 = (dstGfx.y1 + dstGfx.y2) / 2; // Middle
  } else if (numInputs == 2) {
    // Pin 0: upper third, Pin 1: lower third
    int pinSpacing = dstHeight / 3;
    GInfo.y2 = dstGfx.y1 + pinSpacing + (DstPinIndex * pinSpacing);
  } else if (numInputs == 3) {
    // Pin 0: upper quarter, Pin 1: middle, Pin 2: lower quarter
    int pinSpacing = dstHeight / 4;
    GInfo.y2 = dstGfx.y1 + pinSpacing + (DstPinIndex * pinSpacing);
  }

  // Create the connection
  Connection *pConn = new Connection(GInfo, pSrcPin, pDstPin);

  // Connect the output pin to this connection
  pSrcPin->ConnectTo(pConn);

  // Add to component list
  pManager->AddComponent(pConn);

  pManager->GetOutput()->PrintMsg("Connection created successfully!");
}

void AddConnection::Undo() {}

void AddConnection::Redo() {}
