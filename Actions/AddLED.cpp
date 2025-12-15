#include "AddLED.h"
#include "..\ApplicationManager.h"

AddLED::AddLED(ApplicationManager *pApp):Action(pApp)
{
}

AddLED::~AddLED(void)
{
}

void AddLED::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMsg("LED: Click to add the LED");
	pIn->GetPointClicked(Cx, Cy);
	pOut->ClearStatusBar();
}

void AddLED::Execute()
{
	ReadActionParameters();
	
	int Len = UI.LED_Width;
	int Wdth = UI.LED_Height;
	
	GraphicsInfo GInfo;
	
	GInfo.x1 = Cx - Len/2;
	GInfo.x2 = Cx + Len/2;
	GInfo.y1 = Cy - Wdth/2;
	GInfo.y2 = Cy + Wdth/2;
	LED *pA=new LED(GInfo); 
	pManager->AddComponent(pA);
}

void AddLED::Undo()
{}

void AddLED::Redo()
{}
