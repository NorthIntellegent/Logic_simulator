#include "Select.h"
#include "..\ApplicationManager.h"

Select::Select(ApplicationManager *pApp) : Action(pApp)
{
	pSelectedComp = NULL;
}

Select::~Select()
{
}

void Select::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("Select: Click on a component to select/deselect it");

	//Wait for User Input
	pIn->GetPointClicked(Cx, Cy);

	//Clear Status Bar
	pOut->ClearStatusBar();
}

void Select::Execute()
{
	//Get click position
	ReadActionParameters();

	//Get the component at this position
	pSelectedComp = pManager->GetComponentByPosition(Cx, Cy);

	if (pSelectedComp)
	{
		//Toggle selection state
		pSelectedComp->SetSelected(!pSelectedComp->IsSelected());
	}
}

void Select::Undo()
{
	//Toggle selection back
	if (pSelectedComp)
		pSelectedComp->SetSelected(!pSelectedComp->IsSelected());
}

void Select::Redo()
{
	//Toggle selection again
	if (pSelectedComp)
		pSelectedComp->SetSelected(!pSelectedComp->IsSelected());
}
