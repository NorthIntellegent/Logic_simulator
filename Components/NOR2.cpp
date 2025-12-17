#include "NOR2.h"

NOR2::NOR2(const GraphicsInfo &r_GfxInfo, int r_FanOut) : Gate(2, r_FanOut) {
  m_GfxInfo.x1 = r_GfxInfo.x1;
  m_GfxInfo.y1 = r_GfxInfo.y1;
  m_GfxInfo.x2 = r_GfxInfo.x2;
  m_GfxInfo.y2 = r_GfxInfo.y2;
}

void NOR2::Operate() {
  // Calculate the output status as the NORing of the two input pins
  STATUS in1 = m_InputPins[0].getStatus();
  STATUS in2 = m_InputPins[1].getStatus();

  // NOR: output is HIGH only if both inputs are LOW
  if (in1 == LOW && in2 == LOW)
    m_OutputPin.setStatus(HIGH);
  else
    m_OutputPin.setStatus(LOW);
}

// Function Draw
// Draws 2-input NOR gate
void NOR2::Draw(Output *pOut) {
  // Call output class and pass gate drawing info to it.
  pOut->DrawNOR2(m_GfxInfo, IsSelected(), GetLabel());
}

// returns status of outputpin
int NOR2::GetOutPinStatus() { return m_OutputPin.getStatus(); }

// returns status of Inputpin #n
int NOR2::GetInputPinStatus(int n) {
  return m_InputPins[n - 1]
      .getStatus(); // n starts from 1 but array index starts from 0.
}

// Set status of an input pin ot HIGH or LOW
void NOR2::setInputPinStatus(int n, STATUS s) {
  m_InputPins[n - 1].setStatus(s);
}

void NOR2::Save(ofstream &fout) {
  string label = GetLabel();
  if (label == "")
    label = "$";
  fout << "NOR2 " << GetID() << " " << label << " " << m_GfxInfo.x1 << " "
       << m_GfxInfo.y1 << endl;
}

void NOR2::Load(ifstream &fin) {
  string label;
  int id, x, y;
  fin >> id >> label >> x >> y;
  SetID(id);
  if (label == "$")
    label = "";
  SetLabel(label);
  m_GfxInfo.x1 = x;
  m_GfxInfo.y1 = y;
  m_GfxInfo.x2 = x + UI.NOR2_Width;
  m_GfxInfo.y2 = y + UI.NOR2_Height;
}
