#include "LED.h"

LED::LED(const GraphicsInfo &r_GfxInfo) {
  m_GfxInfo.x1 = r_GfxInfo.x1;
  m_GfxInfo.y1 = r_GfxInfo.y1;
  m_GfxInfo.x2 = r_GfxInfo.x2;
  m_GfxInfo.y2 = r_GfxInfo.y2;
  m_InputPin.setComponent(this);
}

void LED::Operate() {
  // LED: just displays its input status
  // The actual display will be handled by Draw based on input status
}

// Function Draw
// Draws LED
void LED::Draw(Output *pOut) {
  // Call output class and pass drawing info to it.
  bool isOn = (m_InputPin.getStatus() == HIGH);
  pOut->DrawLED(m_GfxInfo, IsSelected(), GetLabel(), isOn);
}

// returns status of outputpin - LED has no output pin
int LED::GetOutPinStatus() {
  return -1; // No output pin
}

// returns status of Inputpin #n
int LED::GetInputPinStatus(int n) { return m_InputPin.getStatus(); }

// Set status of an input pin
void LED::setInputPinStatus(int n, STATUS s) { m_InputPin.setStatus(s); }

InputPin *LED::GetInputPin() { return &m_InputPin; }

void LED::Save(ofstream &fout) {
  string label = GetLabel();
  if (label == "")
    label = "$";
  fout << "LED " << GetID() << " " << label << " " << m_GfxInfo.x1 << " "
       << m_GfxInfo.y1 << endl;
}

void LED::Load(ifstream &fin) {
  string label;
  int id, x, y;
  fin >> id >> label >> x >> y;
  SetID(id);
  if (label == "$")
    label = "";
  SetLabel(label);
  m_GfxInfo.x1 = x;
  m_GfxInfo.y1 = y;
  m_GfxInfo.x2 = x + UI.LED_Width;
  m_GfxInfo.y2 = y + UI.LED_Height;
}
