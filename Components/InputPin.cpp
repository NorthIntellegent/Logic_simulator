#include "InputPin.h"

InputPin::InputPin() { m_bConnected = false; }

void InputPin::setComponent(Component *pCmp) { this->pComp = pCmp; }

Component *InputPin::getComponent() { return pComp; }