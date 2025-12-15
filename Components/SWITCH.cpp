#include "SWITCH.h"

SWITCH::SWITCH(const GraphicsInfo &r_GfxInfo, int r_FanOut):m_OutputPin(r_FanOut)
{
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
	m_Status = LOW;	//Default status is LOW
	m_OutputPin.setComponent(this);
}


void SWITCH::Operate()
{
	//Switch: output = current status
	m_OutputPin.setStatus(m_Status);
}


// Function Draw
// Draws Switch
void SWITCH::Draw(Output* pOut)
{
	//Call output class and pass drawing info to it.
	pOut->DrawSWITCH(m_GfxInfo);
}

//returns status of outputpin
int SWITCH::GetOutPinStatus()	
{
	return m_OutputPin.getStatus();
}


//returns status of Inputpin #n - Switch has no input pins
int SWITCH::GetInputPinStatus(int n)	
{
	return -1;	//No input pins
}

//Set status of an input pin - Switch has no input pins
void SWITCH::setInputPinStatus(int n, STATUS s)
{
	//Do nothing - Switch has no input pins
}

void SWITCH::SetStatus(STATUS s)
{
	m_Status = s;
}

STATUS SWITCH::GetStatus()
{
	return m_Status;
}

void SWITCH::Toggle()
{
	if(m_Status == HIGH)
		m_Status = LOW;
	else
		m_Status = HIGH;
}

OutputPin* SWITCH::GetOutputPin()
{
	return &m_OutputPin;
}

void SWITCH::Save(ofstream &fout)
{
	string label = GetLabel();
	if (label == "") label = "$";
	fout << "SWITCH " << GetID() << " " << label << " " << m_GfxInfo.x1 << " " << m_GfxInfo.y1 << " " << m_Status << endl;
}

void SWITCH::Load(ifstream &fin)
{
	string label;
	int id, x, y, status;
	fin >> id >> label >> x >> y >> status;
	SetID(id);
	if (label == "$") label = "";
	SetLabel(label);
	m_GfxInfo.x1 = x;
	m_GfxInfo.y1 = y;
	m_GfxInfo.x2 = x + UI.SWITCH_Width;
	m_GfxInfo.y2 = y + UI.SWITCH_Height;
	m_Status = (STATUS)status;
}
