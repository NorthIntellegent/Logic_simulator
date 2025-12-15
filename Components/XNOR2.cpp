#include "XNOR2.h"

XNOR2::XNOR2(const GraphicsInfo &r_GfxInfo, int r_FanOut):Gate(2, r_FanOut)
{
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
}


void XNOR2::Operate()
{
	//caclulate the output status as the XNORing of the two input pins

	//Add you code here
}


// Function Draw
// Draws 2-input XNOR gate
void XNOR2::Draw(Output* pOut)
{
	//Call output class and pass gate drawing info to it.
	pOut->DrawXNOR2(m_GfxInfo);
}

//returns status of outputpin
int XNOR2::GetOutPinStatus()	
{
	return m_OutputPin.getStatus();
}


//returns status of Inputpin #n
int XNOR2::GetInputPinStatus(int n)	
{
	return m_InputPins[n-1].getStatus();	//n starts from 1 but array index starts from 0.
}

//Set status of an input pin ot HIGH or LOW
void XNOR2::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n-1].setStatus(s);
}

void XNOR2::Save(ofstream &fout)
{
	string label = GetLabel();
	if (label == "") label = "$";
	fout << "XNOR2 " << GetID() << " " << label << " " << m_GfxInfo.x1 << " " << m_GfxInfo.y1 << endl;
}

void XNOR2::Load(ifstream &fin)
{
	string label;
	int id, x, y;
	fin >> id >> label >> x >> y;
	SetID(id);
	if (label == "$") label = "";
	SetLabel(label);
	m_GfxInfo.x1 = x;
	m_GfxInfo.y1 = y;
	m_GfxInfo.x2 = x + UI.XNOR2_Width;
	m_GfxInfo.y2 = y + UI.XNOR2_Height;
}
