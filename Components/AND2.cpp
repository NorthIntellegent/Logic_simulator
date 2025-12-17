#include "AND2.h"

AND2::AND2(const GraphicsInfo &r_GfxInfo, int r_FanOut) : Gate(2, r_FanOut) {
  m_GfxInfo.x1 = r_GfxInfo.x1;
  m_GfxInfo.y1 = r_GfxInfo.y1;
  m_GfxInfo.x2 = r_GfxInfo.x2;
  m_GfxInfo.y2 = r_GfxInfo.y2;
}

void AND2::Operate() {
  // Calculate the output status as the ANDing of the two input pins
  STATUS in1 = m_InputPins[0].getStatus();
  STATUS in2 = m_InputPins[1].getStatus();

  // AND: output is HIGH only if both inputs are HIGH
  if (in1 == HIGH && in2 == HIGH)
    m_OutputPin.setStatus(HIGH);
  else
    m_OutputPin.setStatus(LOW);
}

// Function Draw
// Draws 2-input AND gate
void AND2::Draw(Output *pOut) {
  // Call output class and pass gate drawing info to it.
  pOut->DrawAND2(m_GfxInfo, IsSelected(), GetLabel());
}

// returns status of outputpin
int AND2::GetOutPinStatus() { return m_OutputPin.getStatus(); }

// returns status of Inputpin #n
int AND2::GetInputPinStatus(int n) {
  return m_InputPins[n - 1]
      .getStatus(); // n starts from 1 but array index starts from 0.
}

// Set status of an input pin ot HIGH or LOW
void AND2::setInputPinStatus(int n, STATUS s) {
  m_InputPins[n - 1].setStatus(s);
}

void AND2::Save(ofstream &fout) {
  string label = GetLabel();
  if (label == "")
    label = "$";
  fout << "AND2 " << GetID() << " " << label << " " << m_GfxInfo.x1 << " "
       << m_GfxInfo.y1 << endl;
}

void AND2::Load(ifstream &fin) {
  string label;
  int id, x, y;
  fin >> id >> label >> x >> y;
  SetID(id);
  if (label == "$")
    label = "";
  SetLabel(label);
  m_GfxInfo.x1 = x;
  m_GfxInfo.y1 = y;
  m_GfxInfo.x2 = x + UI.AND2_Width;
  m_GfxInfo.y2 = y + UI.AND2_Height;
}
