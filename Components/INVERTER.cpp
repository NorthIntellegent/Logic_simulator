#include "INVERTER.h"

INVERTER::INVERTER(const GraphicsInfo &r_GfxInfo, int r_FanOut):Gate(1, r_FanOut)
{
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
}


void INVERTER::Operate()
{
	//Inverter: output = NOT(input)

	//Add you code here
}


// Function Draw
// Draws 1-input Inverter gate
void INVERTER::Draw(Output* pOut)
{
	//Call output class and pass gate drawing info to it.
	pOut->DrawINVERTER(m_GfxInfo);
}

//returns status of outputpin
int INVERTER::GetOutPinStatus()	
{
	return m_OutputPin.getStatus();
}


//returns status of Inputpin #n
int INVERTER::GetInputPinStatus(int n)	
{
	return m_InputPins[n-1].getStatus();	//n starts from 1 but array index starts from 0.
}

//Set status of an input pin ot HIGH or LOW
void INVERTER::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n-1].setStatus(s);
}

void INVERTER::Save(ofstream &fout)
{
	string label = GetLabel();
	if (label == "") label = "$";
	fout << "INVERTER " << GetID() << " " << label << " " << m_GfxInfo.x1 << " " << m_GfxInfo.y1 << endl;
}

void INVERTER::Load(ifstream &fin)
{
	string label;
	int id, x, y;
	fin >> id >> label >> x >> y;
	SetID(id);
	if (label == "$") label = "";
	SetLabel(label);
	m_GfxInfo.x1 = x;
	m_GfxInfo.y1 = y;
	m_GfxInfo.x2 = x + UI.INVERTER_Width;
	m_GfxInfo.y2 = y + UI.INVERTER_Height;
}
