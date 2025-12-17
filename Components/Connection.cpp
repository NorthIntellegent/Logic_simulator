#include "Connection.h"

Connection::Connection(const GraphicsInfo &r_GfxInfo, OutputPin *pSrcPin,
                       InputPin *pDstPin)
    : Component(r_GfxInfo)

{
  SrcPin = pSrcPin;
  DstPin = pDstPin;
  if (DstPin) {
    DstPin->setConnected(true); // Mark destination pin as connected
  }
}
void Connection::setSourcePin(OutputPin *pSrcPin) { SrcPin = pSrcPin; }

OutputPin *Connection::getSourcePin() { return SrcPin; }

void Connection::setDestPin(InputPin *pDstPin) { DstPin = pDstPin; }

InputPin *Connection::getDestPin() { return DstPin; }

void Connection::Operate() {
  // Status of connection destination pin = status of connection source pin
  DstPin->setStatus((STATUS)SrcPin->getStatus());
}

void Connection::Draw(Output *pOut) {
  pOut->DrawConnection(m_GfxInfo, IsSelected(), GetLabel());
}

int Connection::GetOutPinStatus() // returns status of outputpin if LED, return
                                  // -1
{
  return DstPin->getStatus();
}

int Connection::GetInputPinStatus(
    int n) // returns status of Inputpin # n if SWITCH, return -1
{
  return SrcPin->getStatus(); // n is ignored as connection has only one input
                              // pin (src pin)
}

void Connection::setInputPinStatus(int n, STATUS s) { SrcPin->setStatus(s); }

void Connection::Save(ofstream &fout) {
  Component *pSrcComp = SrcPin->getComponent();
  Component *pDstComp = DstPin->getComponent();

  int srcID = (pSrcComp) ? pSrcComp->GetID() : -1;
  int dstID = (pDstComp) ? pDstComp->GetID() : -1;
  int pinNum = (pDstComp) ? pDstComp->GetInputPinIndex(DstPin) : -1;

  fout << srcID << " " << dstID << " " << pinNum << endl;
}

void Connection::Load(ifstream &fin) {
  int id1, id2, pin;
  fin >> id1 >> id2 >> pin;
}
