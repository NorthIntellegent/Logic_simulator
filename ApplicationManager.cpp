#include "ApplicationManager.h"
#include "Actions\ActionChangeSwitch.h"
#include "Actions\ActionCopy.h"
#include "Actions\ActionCut.h"
#include "Actions\ActionExit.h"
#include "Actions\ActionMove.h"
#include "Actions\ActionPaste.h"
#include "Actions\ActionProbe.h"
#include "Actions\ActionSimulate.h"
#include "Actions\ActionTruthTable.h"
#include "Actions\AddANDgate2.h"
#include "Actions\AddANDgate3.h"
#include "Actions\AddBuffer.h"
#include "Actions\AddConnection.h"
#include "Actions\AddInverter.h"
#include "Actions\AddLED.h"
#include "Actions\AddLabel.h"
#include "Actions\AddNANDgate2.h"
#include "Actions\AddNORgate2.h"
#include "Actions\AddNORgate3.h"
#include "Actions\AddORgate2.h"
#include "Actions\AddSwitch.h"
#include "Actions\AddXNORgate2.h"
#include "Actions\AddXORgate2.h"
#include "Actions\AddXORgate3.h"
#include "Actions\Delete.h"
#include "Actions\EditLabel.h"
#include "Actions\LoadAction.h"
#include "Actions\SaveAction.h"
#include "Actions\Select.h"
#include "Components\AND2.h"
#include "Components\AND3.h"
#include "Components\BUFFER.h"
#include "Components\Connection.h"
#include "Components\Gate.h"
#include "Components\INVERTER.h"
#include "Components\LED.h"
#include "Components\NAND2.h"
#include "Components\NOR2.h"
#include "Components\NOR3.h"
#include "Components\OR2.h"
#include "Components\SWITCH.h"
#include "Components\XNOR2.h"
#include "Components\XOR2.h"
#include "Components\XOR3.h"
#include <fstream>
#include <iostream>

using namespace std;

ApplicationManager::ApplicationManager() {
  CompCount = 0;
  UndoCount = 0;
  RedoCount = 0;
  m_Clipboard.hasData = false;
  m_Clipboard.typeName = "";

  for (int i = 0; i < MaxCompCount; i++)
    CompList[i] = NULL;

  for (int i = 0; i < MaxActionHistory; i++) {
    UndoStack[i] = NULL;
    RedoStack[i] = NULL;
  }

  // Creates the Input / Output Objects & Initialize the GUI
  OutputInterface = new Output();
  InputInterface = OutputInterface->CreateInput();
}
////////////////////////////////////////////////////////////////////
void ApplicationManager::AddComponent(Component *pComp) {
  CompList[CompCount++] = pComp;
  cout << "Component Added. ID: " << pComp->GetID() << " Count: " << CompCount
       << endl;
}
////////////////////////////////////////////////////////////////////

ActionType ApplicationManager::GetUserAction() {
  // Call input to get what action is reuired from the user
  return InputInterface->GetUserAction();
}
////////////////////////////////////////////////////////////////////

void ApplicationManager::ExecuteAction(ActionType ActType) {
  Action *pAct = NULL;
  cout << "Executing Action Type: " << ActType << endl;

  switch (ActType) {
  case ADD_AND_GATE_2:
    pAct = new AddANDgate2(this);
    break;

  case ADD_OR_GATE_2:
    pAct = new AddORgate2(this);
    break;

  case ADD_NAND_GATE_2:
    pAct = new AddNANDgate2(this);
    break;

  case ADD_NOR_GATE_2:
    pAct = new AddNORgate2(this);
    break;

  case ADD_XOR_GATE_2:
    pAct = new AddXORgate2(this);
    break;

  case ADD_XNOR_GATE_2:
    pAct = new AddXNORgate2(this);
    break;

  case ADD_AND_GATE_3:
    pAct = new AddANDgate3(this);
    break;

  case ADD_NOR_GATE_3:
    pAct = new AddNORgate3(this);
    break;

  case ADD_XOR_GATE_3:
    pAct = new AddXORgate3(this);
    break;

  case ADD_Buff:
    pAct = new AddBuffer(this);
    break;

  case ADD_INV:
    pAct = new AddInverter(this);
    break;

  case ADD_Switch:
    pAct = new AddSwitch(this);
    break;

  case ADD_LED:
    pAct = new AddLED(this);
    break;

  case ADD_Label:
    pAct = new AddLabel(this);
    break;

  case EDIT_Label:
    pAct = new EditLabel(this);
    break;

  case DEL:
    pAct = new Delete(this);
    break;

  case SELECT:
    pAct = new Select(this);
    break;

  case ADD_CONNECTION:
    pAct = new AddConnection(this);
    break;

  case SAVE:
    pAct = new SaveAction(this);
    break;

  case LOAD:
    pAct = new LoadAction(this);
    break;

  case SIM_MODE:
    OutputInterface->ClearDesignToolBar();
    OutputInterface->ClearDrawingArea();
    OutputInterface->CreateSimulationToolBar();
    break;

  case DSN_MODE:
    OutputInterface->ClearDesignToolBar();
    OutputInterface->ClearDrawingArea();
    OutputInterface->CreateDesignToolBar();
    UpdateInterface(); // Redraw all components
    break;

  case Change_Switch:
    pAct = new ActionChangeSwitch(this);
    break;

  case Simulate:
    pAct = new ActionSimulate(this);
    break;

  case Create_TruthTable:
    pAct = new ActionTruthTable(this);
    break;

  case Probe:
    pAct = new ActionProbe(this);
    break;

  case MOVE:
    pAct = new ActionMove(this);
    break;

  case COPY:
    pAct = new ActionCopy(this);
    break;

  case CUT:
    pAct = new ActionCut(this);
    break;

  case PASTE:
    pAct = new ActionPaste(this);
    break;

  case EXIT:
    pAct = new ActionExit(this);
    break;

  case UNDO:
    PerformUndo();
    break;

  case REDO:
    PerformRedo();
    break;

  case STATUS_BAR:
  case DSN_TOOL:
    // Clicks on empty areas - ignore
    break;
  }
  if (pAct) {
    pAct->Execute();

    // For undoable actions (Move, Select), save to undo stack
    // For others, delete immediately
    ActionType actType = ActType;
    if (actType == MOVE || actType == SELECT) {
      AddToUndoStack(pAct);
    } else {
      delete pAct;
    }
    pAct = NULL;
  }
}
////////////////////////////////////////////////////////////////////

void ApplicationManager::UpdateInterface() {
  OutputInterface->ClearDrawingArea();
  for (int i = 0; i < CompCount; i++)
    CompList[i]->Draw(OutputInterface);
}

////////////////////////////////////////////////////////////////////
Input *ApplicationManager::GetInput() { return InputInterface; }

////////////////////////////////////////////////////////////////////
Output *ApplicationManager::GetOutput() { return OutputInterface; }

Component *ApplicationManager::GetComponentByPosition(int x, int y) {
  cout << "Searching for component at (" << x << ", " << y << ")" << endl;
  for (int i = 0; i < CompCount; i++) {
    bool isInside = CompList[i]->Inside(x, y);
    cout << "Checking Component " << i << ": Inside(" << x << "," << y
         << ") = " << isInside << endl;
    if (isInside)
      return CompList[i];
  }
  cout << "No component found." << endl;
  return NULL;
}

void ApplicationManager::DeleteComponent(Component *pComp) {
  if (!pComp)
    return;

  // If it's a component (not connection), delete its connections first
  if (dynamic_cast<Connection *>(pComp) == NULL) {
    for (int i = 0; i < CompCount; i++) {
      Connection *pConn = dynamic_cast<Connection *>(CompList[i]);
      if (pConn) {
        if (pConn->getSourcePin()->getComponent() == pComp ||
            pConn->getDestPin()->getComponent() == pComp) {
          DeleteComponent(pConn);
          i--; // Decrement i because CompList shifted
        }
      }
    }
  }

  // Remove from CompList
  for (int i = 0; i < CompCount; i++) {
    if (CompList[i] == pComp) {
      delete CompList[i];
      CompList[i] = CompList[CompCount - 1];
      CompList[CompCount - 1] = NULL;
      CompCount--;
      return;
    }
  }
}

////////////////////////////////////////////////////////////////////

void ApplicationManager::SaveCircuit(string filename) {
  ofstream fout(filename);
  if (!fout.is_open())
    return;

  // Count non-connection components
  int nonConnCount = 0;
  for (int i = 0; i < CompCount; i++) {
    if (dynamic_cast<Connection *>(CompList[i]) == NULL)
      nonConnCount++;
  }

  fout << nonConnCount << endl;

  // Save Components
  for (int i = 0; i < CompCount; i++) {
    if (dynamic_cast<Connection *>(CompList[i]) == NULL)
      CompList[i]->Save(fout);
  }

  fout << "Connections" << endl;

  // Save Connections
  for (int i = 0; i < CompCount; i++) {
    if (dynamic_cast<Connection *>(CompList[i]) != NULL)
      CompList[i]->Save(fout);
  }

  fout << "-1" << endl;
  fout.close();
}

void ApplicationManager::LoadCircuit(string filename) {
  ifstream fin(filename);
  if (!fin.is_open())
    return;

  // Clear existing components
  for (int i = 0; i < CompCount; i++)
    delete CompList[i];
  CompCount = 0;

  int count;
  fin >> count;

  string type;
  GraphicsInfo GfxInfo;
  // Initialize GfxInfo with dummy values, Load will overwrite
  GfxInfo.x1 = 0;
  GfxInfo.y1 = 0;
  GfxInfo.x2 = 0;
  GfxInfo.y2 = 0;

  for (int i = 0; i < count; i++) {
    fin >> type;
    Component *pComp = NULL;

    if (type == "AND2")
      pComp = new AND2(GfxInfo, AND2_FANOUT);
    else if (type == "OR2")
      pComp = new OR2(GfxInfo, OR2_FANOUT);
    else if (type == "NAND2")
      pComp = new NAND2(GfxInfo, NAND2_FANOUT);
    else if (type == "NOR2")
      pComp = new NOR2(GfxInfo, NOR2_FANOUT);
    else if (type == "XOR2")
      pComp = new XOR2(GfxInfo, XOR2_FANOUT);
    else if (type == "XNOR2")
      pComp = new XNOR2(GfxInfo, XNOR2_FANOUT);
    else if (type == "AND3")
      pComp = new AND3(GfxInfo, AND3_FANOUT);
    else if (type == "NOR3")
      pComp = new NOR3(GfxInfo, NOR3_FANOUT);
    else if (type == "XOR3")
      pComp = new XOR3(GfxInfo, XOR3_FANOUT);
    else if (type == "BUFFER")
      pComp = new BUFFER(GfxInfo, BUFFER_FANOUT);
    else if (type == "INVERTER")
      pComp = new INVERTER(GfxInfo, INVERTER_FANOUT);
    else if (type == "SWITCH")
      pComp = new SWITCH(GfxInfo, SWITCH_FANOUT);
    else if (type == "LED")
      pComp = new LED(GfxInfo);
    // TODO: Add other component types here

    if (pComp) {
      pComp->Load(fin);
      AddComponent(pComp);
    }
  }

  fin >> type; // Read "Connections"

  while (fin >> type && type != "-1") {
    int srcID = stoi(type);
    int dstID, pinNum;
    fin >> dstID >> pinNum;

    Component *pSrc = NULL;
    Component *pDst = NULL;

    // Find components
    for (int i = 0; i < CompCount; i++) {
      if (CompList[i]->GetID() == srcID)
        pSrc = CompList[i];
      if (CompList[i]->GetID() == dstID)
        pDst = CompList[i];
    }

    if (pSrc && pDst) {
      OutputPin *pSrcPin = NULL;
      InputPin *pDstPin = NULL;

      // Assuming Source is a Gate for now
      Gate *pSrcGate = dynamic_cast<Gate *>(pSrc);
      if (pSrcGate)
        pSrcPin = pSrcGate->GetOutputPin();

      // Assuming Dest is a Gate
      Gate *pDstGate = dynamic_cast<Gate *>(pDst);
      if (pDstGate)
        pDstPin =
            pDstGate->GetInputPin(pinNum - 1); // PinNum is 1-based in file

      if (pSrcPin && pDstPin) {
        Connection *pConn = new Connection(GfxInfo, pSrcPin, pDstPin);
        AddComponent(pConn);
      }
    }
  }

  fin.close();
}

ApplicationManager::~ApplicationManager() {
  for (int i = 0; i < CompCount; i++)
    delete CompList[i];
  delete OutputInterface;
  delete InputInterface;
}

// Accessor methods for simulation
int ApplicationManager::GetComponentCount() const { return CompCount; }

Component *ApplicationManager::GetComponent(int index) const {
  if (index >= 0 && index < CompCount)
    return CompList[index];
  return NULL;
}

Component *ApplicationManager::GetComponentByID(int id) const {
  for (int i = 0; i < CompCount; i++) {
    if (CompList[i]->GetID() == id)
      return CompList[i];
  }
  return NULL;
}

// Multi-selection helpers
int ApplicationManager::GetSelectedCount() const {
  int count = 0;
  for (int i = 0; i < CompCount; i++) {
    if (CompList[i] && CompList[i]->IsSelected())
      count++;
  }
  return count;
}

void ApplicationManager::ClearAllSelections() {
  for (int i = 0; i < CompCount; i++) {
    if (CompList[i])
      CompList[i]->SetSelected(false);
  }
}

void ApplicationManager::DeleteAllSelected() {
  // Delete from end to avoid index shifting issues
  for (int i = CompCount - 1; i >= 0; i--) {
    if (CompList[i] && CompList[i]->IsSelected()) {
      DeleteComponent(CompList[i]);
    }
  }
}

void ApplicationManager::MoveAllSelected(int dx, int dy) {
  for (int i = 0; i < CompCount; i++) {
    if (CompList[i] && CompList[i]->IsSelected()) {
      GraphicsInfo gfx = CompList[i]->GetGraphicsInfo();
      gfx.x1 += dx;
      gfx.y1 += dy;
      gfx.x2 += dx;
      gfx.y2 += dy;
      CompList[i]->SetGraphicsInfo(gfx);
    }
  }
}

// Undo/Redo System Implementation
void ApplicationManager::AddToUndoStack(Action *pAction) {
  if (UndoCount >= MaxActionHistory) {
    // Stack full, remove oldest action
    delete UndoStack[0];
    for (int i = 0; i < MaxActionHistory - 1; i++) {
      UndoStack[i] = UndoStack[i + 1];
    }
    UndoCount--;
  }
  UndoStack[UndoCount++] = pAction;

  // Clear redo stack when new action is performed
  ClearRedoStack();
}

void ApplicationManager::PerformUndo() {
  if (UndoCount <= 0) {
    OutputInterface->PrintMsg("Nothing to undo!");
    return;
  }

  // Get last action and undo it
  Action *pAction = UndoStack[--UndoCount];
  UndoStack[UndoCount] = NULL;

  pAction->Undo();

  // Add to redo stack
  if (RedoCount < MaxActionHistory) {
    RedoStack[RedoCount++] = pAction;
  } else {
    delete pAction;
  }

  UpdateInterface();
  OutputInterface->PrintMsg("Undo performed");
}

void ApplicationManager::PerformRedo() {
  if (RedoCount <= 0) {
    OutputInterface->PrintMsg("Nothing to redo!");
    return;
  }

  // Get last undone action and redo it
  Action *pAction = RedoStack[--RedoCount];
  RedoStack[RedoCount] = NULL;

  pAction->Redo();

  // Add back to undo stack
  if (UndoCount < MaxActionHistory) {
    UndoStack[UndoCount++] = pAction;
  } else {
    delete pAction;
  }

  UpdateInterface();
  OutputInterface->PrintMsg("Redo performed");
}

void ApplicationManager::ClearRedoStack() {
  for (int i = 0; i < RedoCount; i++) {
    if (RedoStack[i]) {
      delete RedoStack[i];
      RedoStack[i] = NULL;
    }
  }
  RedoCount = 0;
}