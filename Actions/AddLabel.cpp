#include "AddLabel.h"
#include "..\ApplicationManager.h"

AddLabel::AddLabel(ApplicationManager *pApp) : Action(pApp)
{
	pComp = NULL;
}

AddLabel::~AddLabel()
{
}

void AddLabel::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("Add Label: Click on a component");

	//Wait for User to click on component
	pIn->GetPointClicked(Cx, Cy);

	//Get the component at this position
	pComp = pManager->GetComponentByPosition(Cx, Cy);

	if (!pComp)
	{
		pOut->PrintMsg("No component found at this position");
		return;
	}

	//Get label text from user
	pOut->PrintMsg("Enter label text:");
	Label = pIn->GetString(pOut);

	//Clear Status Bar
	pOut->ClearStatusBar();
}

void AddLabel::Execute()
{
	//Get parameters
	ReadActionParameters();

	//Set the label if component was found
	if (pComp && Label != "")
	{
		pComp->SetLabel(Label);
	}
}

void AddLabel::Undo()
{
	//Remove the label
	if (pComp)
		pComp->SetLabel("");
}

void AddLabel::Redo()
{
	//Re-apply the label
	if (pComp)
		pComp->SetLabel(Label);
}
