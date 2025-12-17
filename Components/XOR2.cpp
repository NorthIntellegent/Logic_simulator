#include "XOR2.h"

XOR2::XOR2(const GraphicsInfo &r_GfxInfo, int r_FanOut) : Gate(2, r_FanOut) {
  m_GfxInfo.x1 = r_GfxInfo.x1;
  m_GfxInfo.y1 = r_GfxInfo.y1;
  m_GfxInfo.x2 = r_GfxInfo.x2;
  m_GfxInfo.y2 = r_GfxInfo.y2;
}

void XOR2::Operate() {
  // Calculate the output status as the XORing of the two input pins
  STATUS in1 = m_InputPins[0].getStatus();
  STATUS in2 = m_InputPins[1].getStatus();

  // XOR: output is HIGH only if inputs are different
  if (in1 != in2)
    m_OutputPin.setStatus(HIGH);
  else
    m_OutputPin.setStatus(LOW);
}

// Function Draw
// Draws 2-input XOR gate
void XOR2::Draw(Output *pOut) {
  // Call output class and pass gate drawing info to it.
  pOut->DrawXOR2(m_GfxInfo, IsSelected(), GetLabel());
}

// returns status of outputpin
int XOR2::GetOutPinStatus() { return m_OutputPin.getStatus(); }

// returns status of Inputpin #n
int XOR2::GetInputPinStatus(int n) {
  return m_InputPins[n - 1]
      .getStatus(); // n starts from 1 but array index starts from 0.
}

// Set status of an input pin ot HIGH or LOW
void XOR2::setInputPinStatus(int n, STATUS s) {
  m_InputPins[n - 1].setStatus(s);
}

void XOR2::Save(ofstream &fout) {
  string label = GetLabel();
  if (label == "")
    label = "$";
  fout << "XOR2 " << GetID() << " " << label << " " << m_GfxInfo.x1 << " "
       << m_GfxInfo.y1 << endl;
}

void XOR2::Load(ifstream &fin) {
  string label;
  int id, x, y;
  fin >> id >> label >> x >> y;
  SetID(id);
  if (label == "$")
    label = "";
  SetLabel(label);
  m_GfxInfo.x1 = x;
  m_GfxInfo.y1 = y;
  m_GfxInfo.x2 = x + UI.XOR2_Width;
  m_GfxInfo.y2 = y + UI.XOR2_Height;
}
