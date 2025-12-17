#include "AND3.h"

AND3::AND3(const GraphicsInfo &r_GfxInfo, int r_FanOut) : Gate(3, r_FanOut) {
  m_GfxInfo.x1 = r_GfxInfo.x1;
  m_GfxInfo.y1 = r_GfxInfo.y1;
  m_GfxInfo.x2 = r_GfxInfo.x2;
  m_GfxInfo.y2 = r_GfxInfo.y2;
}

void AND3::Operate() {
  // Calculate the output status as the ANDing of the three input pins
  STATUS in1 = m_InputPins[0].getStatus();
  STATUS in2 = m_InputPins[1].getStatus();
  STATUS in3 = m_InputPins[2].getStatus();

  // AND: output is HIGH only if all inputs are HIGH
  if (in1 == HIGH && in2 == HIGH && in3 == HIGH)
    m_OutputPin.setStatus(HIGH);
  else
    m_OutputPin.setStatus(LOW);
}

// Function Draw
// Draws 3-input AND gate
void AND3::Draw(Output *pOut) {
  // Call output class and pass gate drawing info to it.
  pOut->DrawAND3(m_GfxInfo, IsSelected(), GetLabel());
}

// returns status of outputpin
int AND3::GetOutPinStatus() { return m_OutputPin.getStatus(); }

// returns status of Inputpin #n
int AND3::GetInputPinStatus(int n) {
  return m_InputPins[n - 1]
      .getStatus(); // n starts from 1 but array index starts from 0.
}

// Set status of an input pin ot HIGH or LOW
void AND3::setInputPinStatus(int n, STATUS s) {
  m_InputPins[n - 1].setStatus(s);
}

void AND3::Save(ofstream &fout) {
  string label = GetLabel();
  if (label == "")
    label = "$";
  fout << "AND3 " << GetID() << " " << label << " " << m_GfxInfo.x1 << " "
       << m_GfxInfo.y1 << endl;
}

void AND3::Load(ifstream &fin) {
  string label;
  int id, x, y;
  fin >> id >> label >> x >> y;
  SetID(id);
  if (label == "$")
    label = "";
  SetLabel(label);
  m_GfxInfo.x1 = x;
  m_GfxInfo.y1 = y;
  m_GfxInfo.x2 = x + UI.AND3_Width;
  m_GfxInfo.y2 = y + UI.AND3_Height;
}
