#include "Gate.h"

//Gate Constructor
//Parameters:
//r_Inputs: no. of gate's input pins
//r_FanOut: Fan out of the gate's output pin
Gate::Gate(int r_Inputs, int r_FanOut):m_OutputPin(r_FanOut)
{
	//Allocate number of input pins (equals r_Inputs)
	m_InputPins = new InputPin[r_Inputs];
	m_Inputs = r_Inputs;	//set no. of inputs of that gate
	
	//Associate all input pins to this gate
	for(int i=0; i<m_Inputs; i++)
		m_InputPins[i].setComponent(this);

	m_OutputPin.setComponent(this);
}

int Gate::GetInputPinIndex(InputPin* pPin)
{
	for(int i=0; i<m_Inputs; i++)
	{
		if(&m_InputPins[i] == pPin) return i+1; // Pin numbers are 1-based
	}
	return -1;
}

OutputPin* Gate::GetOutputPin()
{
	return &m_OutputPin;
}

InputPin* Gate::GetInputPin(int n)
{
	if(n >= 0 && n < m_Inputs)
		return &m_InputPins[n];
	return NULL;
}