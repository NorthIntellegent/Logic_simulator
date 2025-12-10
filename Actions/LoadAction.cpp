#include "LoadAction.h"
#include "..\ApplicationManager.h"

LoadAction::LoadAction(ApplicationManager *pApp) : Action(pApp)
{
}

LoadAction::~LoadAction()
{
}

void LoadAction::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("Load Circuit: Enter filename (e.g., circuit.txt):");

	//Get filename from user
	Filename = pIn->GetString(pOut);

	//Clear Status Bar
	pOut->ClearStatusBar();
}

void LoadAction::Execute()
{
	//Get filename
	ReadActionParameters();

	//Call ApplicationManager to load the circuit
	if (Filename != "")
	{
		pManager->LoadCircuit(Filename);
		
		Output* pOut = pManager->GetOutput();
		pOut->PrintMsg("Circuit loaded from " + Filename);
	}
}

void LoadAction::Undo()
{
	//No undo for load operation
}

void LoadAction::Redo()
{
	//No redo for load operation
}
