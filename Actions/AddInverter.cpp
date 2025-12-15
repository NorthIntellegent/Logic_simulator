#include "AddInverter.h"
#include "..\ApplicationManager.h"

AddInverter::AddInverter(ApplicationManager *pApp):Action(pApp)
{
}

AddInverter::~AddInverter(void)
{
}

void AddInverter::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMsg("Inverter: Click to add the inverter");
	pIn->GetPointClicked(Cx, Cy);
	pOut->ClearStatusBar();
}

void AddInverter::Execute()
{
	ReadActionParameters();
	
	int Len = UI.INVERTER_Width;
	int Wdth = UI.INVERTER_Height;
	
	GraphicsInfo GInfo;
	
	GInfo.x1 = Cx - Len/2;
	GInfo.x2 = Cx + Len/2;
	GInfo.y1 = Cy - Wdth/2;
	GInfo.y2 = Cy + Wdth/2;
	INVERTER *pA=new INVERTER(GInfo, INVERTER_FANOUT); 
	pManager->AddComponent(pA);
}

void AddInverter::Undo()
{}

void AddInverter::Redo()
{}
