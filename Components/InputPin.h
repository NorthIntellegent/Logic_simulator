#ifndef _INPUTPIN_H
#define _INPUTPIN_H

#include "Pin.h"
class Component; // Forward class declaration

class InputPin : public Pin // inherited from class Pin
{
  Component *pComp;  // Component at which this pin is associated
  bool m_bConnected; // Whether this pin has an incoming connection
public:
  InputPin();
  void setComponent(Component *pCmp); // sets the component of this input pin
  Component *getComponent();          // returns the component of this input pin
  void setConnected(bool connected) { m_bConnected = connected; }
  bool isConnected() const { return m_bConnected; }
};

#endif