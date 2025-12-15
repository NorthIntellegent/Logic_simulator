#include "OR2.h"

OR2::OR2(const GraphicsInfo &r_GfxInfo, int r_FanOut):Gate(2, r_FanOut)
{
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
}


void OR2::Operate()
{
	//caclulate the output status as the ORing of the two input pins

	//Add you code here
}


// Function Draw
// Draws 2-input OR gate
void OR2::Draw(Output* pOut)
{
	//Call output class and pass gate drawing info to it.
	pOut->DrawOR2(m_GfxInfo);
}

//returns status of outputpin
int OR2::GetOutPinStatus()	
{
	return m_OutputPin.getStatus();
}


//returns status of Inputpin #n
int OR2::GetInputPinStatus(int n)	
{
	return m_InputPins[n-1].getStatus();	//n starts from 1 but array index starts from 0.
}

//Set status of an input pin ot HIGH or LOW
void OR2::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n-1].setStatus(s);
}

void OR2::Save(ofstream &fout)
{
	string label = GetLabel();
	if (label == "") label = "$";
	fout << "OR2 " << GetID() << " " << label << " " << m_GfxInfo.x1 << " " << m_GfxInfo.y1 << endl;
}

void OR2::Load(ifstream &fin)
{
	string label;
	int id, x, y;
	fin >> id >> label >> x >> y;
	SetID(id);
	if (label == "$") label = "";
	SetLabel(label);
	m_GfxInfo.x1 = x;
	m_GfxInfo.y1 = y;
	m_GfxInfo.x2 = x + UI.OR2_Width;
	m_GfxInfo.y2 = y + UI.OR2_Height;
}
