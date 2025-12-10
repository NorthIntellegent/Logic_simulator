#include "SaveAction.h"
#include "..\ApplicationManager.h"

SaveAction::SaveAction(ApplicationManager *pApp) : Action(pApp)
{
}

SaveAction::~SaveAction()
{
}

void SaveAction::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("Save Circuit: Enter filename (e.g., circuit.txt):");

	//Get filename from user
	Filename = pIn->GetString(pOut);

	//Clear Status Bar
	pOut->ClearStatusBar();
}

void SaveAction::Execute()
{
	//Get filename
	ReadActionParameters();

	//Call ApplicationManager to save the circuit
	if (Filename != "")
	{
		pManager->SaveCircuit(Filename);
		
		Output* pOut = pManager->GetOutput();
		pOut->PrintMsg("Circuit saved to " + Filename);
	}
}

void SaveAction::Undo()
{
	//No undo for save operation
}

void SaveAction::Redo()
{
	//No redo for save operation
}
