#include "AddBuffer.h"
#include "..\ApplicationManager.h"

AddBuffer::AddBuffer(ApplicationManager *pApp):Action(pApp)
{
}

AddBuffer::~AddBuffer(void)
{
}

void AddBuffer::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMsg("Buffer: Click to add the buffer");
	pIn->GetPointClicked(Cx, Cy);
	pOut->ClearStatusBar();
}

void AddBuffer::Execute()
{
	ReadActionParameters();
	
	int Len = UI.BUFFER_Width;
	int Wdth = UI.BUFFER_Height;
	
	GraphicsInfo GInfo;
	
	GInfo.x1 = Cx - Len/2;
	GInfo.x2 = Cx + Len/2;
	GInfo.y1 = Cy - Wdth/2;
	GInfo.y2 = Cy + Wdth/2;
	BUFFER *pA=new BUFFER(GInfo, BUFFER_FANOUT); 
	pManager->AddComponent(pA);
}

void AddBuffer::Undo()
{}

void AddBuffer::Redo()
{}
