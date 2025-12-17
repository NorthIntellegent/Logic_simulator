#include "BUFFER.h"

BUFFER::BUFFER(const GraphicsInfo &r_GfxInfo, int r_FanOut)
    : Gate(1, r_FanOut) {
  m_GfxInfo.x1 = r_GfxInfo.x1;
  m_GfxInfo.y1 = r_GfxInfo.y1;
  m_GfxInfo.x2 = r_GfxInfo.x2;
  m_GfxInfo.y2 = r_GfxInfo.y2;
}

void BUFFER::Operate() {
  // Buffer: output = input
  STATUS in1 = m_InputPins[0].getStatus();
  m_OutputPin.setStatus(in1);
}

// Function Draw
// Draws 1-input Buffer gate
void BUFFER::Draw(Output *pOut) {
  // Call output class and pass gate drawing info to it.
  pOut->DrawBUFFER(m_GfxInfo, IsSelected(), GetLabel());
}

// returns status of outputpin
int BUFFER::GetOutPinStatus() { return m_OutputPin.getStatus(); }

// returns status of Inputpin #n
int BUFFER::GetInputPinStatus(int n) {
  return m_InputPins[n - 1]
      .getStatus(); // n starts from 1 but array index starts from 0.
}

// Set status of an input pin ot HIGH or LOW
void BUFFER::setInputPinStatus(int n, STATUS s) {
  m_InputPins[n - 1].setStatus(s);
}

void BUFFER::Save(ofstream &fout) {
  string label = GetLabel();
  if (label == "")
    label = "$";
  fout << "BUFFER " << GetID() << " " << label << " " << m_GfxInfo.x1 << " "
       << m_GfxInfo.y1 << endl;
}

void BUFFER::Load(ifstream &fin) {
  string label;
  int id, x, y;
  fin >> id >> label >> x >> y;
  SetID(id);
  if (label == "$")
    label = "";
  SetLabel(label);
  m_GfxInfo.x1 = x;
  m_GfxInfo.y1 = y;
  m_GfxInfo.x2 = x + UI.BUFFER_Width;
  m_GfxInfo.y2 = y + UI.BUFFER_Height;
}
