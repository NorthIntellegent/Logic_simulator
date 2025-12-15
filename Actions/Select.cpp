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

	Output* pOut = pManager->GetOutput();

	if (pSelectedComp)
	{
		//Toggle selection state
		pSelectedComp->SetSelected(!pSelectedComp->IsSelected());

		//Display component info in status bar
		if (pSelectedComp->IsSelected())
		{
			string label = pSelectedComp->GetLabel();
			if (label != "")
				pOut->PrintMsg("Selected: " + label);
			else
				pOut->PrintMsg("Selected: " + pSelectedComp->GetTypeName());
		}
		else
		{
			pOut->PrintMsg("Component deselected");
		}

		//Update interface to show highlighting
		pManager->UpdateInterface();
	}
	else
	{
		pOut->PrintMsg("No component at this location");
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
