#include "ActionPaste.h"
#include "..\ApplicationManager.h"
#include "..\Components\AND2.h"
#include "..\Components\AND3.h"
#include "..\Components\BUFFER.h"
#include "..\Components\Component.h"
#include "..\Components\INVERTER.h"
#include "..\Components\LED.h"
#include "..\Components\NAND2.h"
#include "..\Components\NOR2.h"
#include "..\Components\NOR3.h"
#include "..\Components\OR2.h"
#include "..\Components\SWITCH.h"
#include "..\Components\XNOR2.h"
#include "..\Components\XOR2.h"
#include "..\Components\XOR3.h"
#include "..\GUI\Input.h"
#include "..\GUI\Output.h"

ActionPaste::ActionPaste(ApplicationManager *pApp) : Action(pApp) {
  m_pPastedComp = NULL;
  m_PasteX = m_PasteY = 0;
}

void ActionPaste::ReadActionParameters() {
  Output *pOut = pManager->GetOutput();
  Input *pIn = pManager->GetInput();

  if (!pManager->HasClipboardData()) {
    pOut->PrintMsg("Clipboard is empty! Copy or cut a component first.");
    return;
  }

  pOut->PrintMsg("Click where to paste the component");
  pIn->GetPointClicked(m_PasteX, m_PasteY);

  pOut->ClearStatusBar();
}

void ActionPaste::Execute() {
  ReadActionParameters();

  if (!pManager->HasClipboardData())
    return;

  Output *pOut = pManager->GetOutput();

  // Get type name from clipboard
  string typeName = pManager->GetClipboardTypeName();

  // Use default gate size
  int width = UI.AND2_Width;
  int height = UI.AND2_Height;

  GraphicsInfo GInfo;
  GInfo.x1 = m_PasteX - width / 2;
  GInfo.y1 = m_PasteY - height / 2;
  GInfo.x2 = GInfo.x1 + width;
  GInfo.y2 = GInfo.y1 + height;

  // Create new component based on type
  Component *pNewComp = NULL;

  if (typeName == "AND2") {
    pNewComp = new AND2(GInfo, AND2_FANOUT);
  } else if (typeName == "OR2") {
    pNewComp = new OR2(GInfo, OR2_FANOUT);
  } else if (typeName == "NAND2") {
    pNewComp = new NAND2(GInfo, NAND2_FANOUT);
  } else if (typeName == "NOR2") {
    pNewComp = new NOR2(GInfo, NOR2_FANOUT);
  } else if (typeName == "XOR2") {
    pNewComp = new XOR2(GInfo, XOR2_FANOUT);
  } else if (typeName == "XNOR2") {
    pNewComp = new XNOR2(GInfo, XNOR2_FANOUT);
  } else if (typeName == "AND3") {
    pNewComp = new AND3(GInfo, AND3_FANOUT);
  } else if (typeName == "NOR3") {
    pNewComp = new NOR3(GInfo, NOR3_FANOUT);
  } else if (typeName == "XOR3") {
    pNewComp = new XOR3(GInfo, XOR3_FANOUT);
  } else if (typeName == "BUFFER") {
    pNewComp = new BUFFER(GInfo, BUFFER_FANOUT);
  } else if (typeName == "INVERTER") {
    pNewComp = new INVERTER(GInfo, INVERTER_FANOUT);
  } else if (typeName == "SWITCH") {
    pNewComp = new SWITCH(GInfo, SWITCH_FANOUT);
  } else if (typeName == "LED") {
    pNewComp = new LED(GInfo);
  } else {
    pOut->PrintMsg("Cannot paste this component type!");
    return;
  }

  if (pNewComp) {
    m_pPastedComp = pNewComp;
    pManager->AddComponent(pNewComp);
    pManager->UpdateInterface();
    pOut->PrintMsg("Component pasted successfully!");
  }
}

void ActionPaste::Undo() {
  if (m_pPastedComp) {
    pManager->DeleteComponent(m_pPastedComp);
    m_pPastedComp = NULL;
    pManager->UpdateInterface();
  }
}

void ActionPaste::Redo() {
  // Would need to recreate component - complex, skip
}
