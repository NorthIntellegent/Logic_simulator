#include "AddXORgate3.h"
#include "..\ApplicationManager.h"

AddXORgate3::AddXORgate3(ApplicationManager *pApp):Action(pApp)
{
}

AddXORgate3::~AddXORgate3(void)
{
}

void AddXORgate3::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMsg("3-Input XOR Gate: Click to add the gate");
	pIn->GetPointClicked(Cx, Cy);
	pOut->ClearStatusBar();
}

void AddXORgate3::Execute()
{
	ReadActionParameters();
	
	int Len = UI.XOR3_Width;
	int Wdth = UI.XOR3_Height;
	
	GraphicsInfo GInfo;
	
	GInfo.x1 = Cx - Len/2;
	GInfo.x2 = Cx + Len/2;
	GInfo.y1 = Cy - Wdth/2;
	GInfo.y2 = Cy + Wdth/2;
	XOR3 *pA=new XOR3(GInfo, XOR3_FANOUT); 
	pManager->AddComponent(pA);
}

void AddXORgate3::Undo()
{}

void AddXORgate3::Redo()
{}
