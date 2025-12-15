#ifndef _LED_H
#define _LED_H

/*
  Class LED
  -----------
  represent an LED (output indicator) component
  Has only an input pin, no output pins
*/

#include "Component.h"
#include "InputPin.h"

class LED:public Component
{
private:
	InputPin m_InputPin;	//The LED input pin
public:
	LED(const GraphicsInfo &r_GfxInfo);
	virtual void Operate();	//Displays status based on input
	virtual void Draw(Output* pOut);	//Draws the LED

	virtual int GetOutPinStatus();	//returns -1 (no output pin)
	virtual int GetInputPinStatus(int n);	//returns status of input pin

	virtual void setInputPinStatus(int n, STATUS s);	//set status of input pin

	InputPin* GetInputPin();

	virtual void Save(ofstream &fout);
	virtual void Load(ifstream &fin);

};

#endif
