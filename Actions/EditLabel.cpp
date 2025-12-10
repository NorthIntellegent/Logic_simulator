#include "EditLabel.h"
#include "..\ApplicationManager.h"

EditLabel::EditLabel(ApplicationManager *pApp) : Action(pApp)
{
	pComp = NULL;
}

EditLabel::~EditLabel()
{
}

void EditLabel::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("Edit Label: Click on a component");

	//Wait for User to click on component
	pIn->GetPointClicked(Cx, Cy);

	//Get the component at this position
	pComp = pManager->GetComponentByPosition(Cx, Cy);

	if (!pComp)
	{
		pOut->PrintMsg("No component found at this position");
		return;
	}

	//Save old label
	OldLabel = pComp->GetLabel();

	//Get new label text from user
	pOut->PrintMsg("Current label: " + OldLabel + " | Enter new label:");
	NewLabel = pIn->GetString(pOut);

	//Clear Status Bar
	pOut->ClearStatusBar();
}

void EditLabel::Execute()
{
	//Get parameters
	ReadActionParameters();

	//Update the label if component was found
	if (pComp && NewLabel != "")
	{
		pComp->SetLabel(NewLabel);
	}
}

void EditLabel::Undo()
{
	//Restore old label
	if (pComp)
		pComp->SetLabel(OldLabel);
}

void EditLabel::Redo()
{
	//Re-apply new label
	if (pComp)
		pComp->SetLabel(NewLabel);
}
