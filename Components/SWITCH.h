#ifndef _SWITCH_H
#define _SWITCH_H

/*
  Class SWITCH
  -----------
  represent a Switch (input source) component
  Has only an output pin, no input pins
*/

#include "Component.h"
#include "OutputPin.h"

class SWITCH:public Component
{
private:
	OutputPin m_OutputPin;	//The Switch output pin
	STATUS m_Status;		//Current status of the switch (HIGH or LOW)
public:
	SWITCH(const GraphicsInfo &r_GfxInfo, int r_FanOut);
	virtual void Operate();	//Sets the output based on switch status
	virtual void Draw(Output* pOut);	//Draws the switch

	virtual int GetOutPinStatus();	//returns status of outputpin
	virtual int GetInputPinStatus(int n);	//returns -1 (no input pins)

	virtual void setInputPinStatus(int n, STATUS s);	//does nothing for switch

	void SetStatus(STATUS s);	//Set switch status
	STATUS GetStatus();			//Get switch status
	void Toggle();				//Toggle switch status

	OutputPin* GetOutputPin();

	virtual void Save(ofstream &fout);
	virtual void Load(ifstream &fin);

};

#endif
