#include "ApplicationManager.h"
#include "Actions\AddANDgate2.h"
#include "Actions\AddLabel.h"
#include "Actions\EditLabel.h"
#include "Actions\Delete.h"
#include "Actions\Select.h"
#include "Actions\SaveAction.h"
#include "Actions\LoadAction.h"
#include "Components\Connection.h"
#include "Components\AND2.h"
#include "Components\Gate.h"
#include <fstream>
#include <iostream>

using namespace std;

ApplicationManager::ApplicationManager()
{
	CompCount = 0;

	for(int i=0; i<MaxCompCount; i++)
		CompList[i] = NULL;

	//Creates the Input / Output Objects & Initialize the GUI
	OutputInterface = new Output();
	InputInterface = OutputInterface->CreateInput();
}
////////////////////////////////////////////////////////////////////
void ApplicationManager::AddComponent(Component* pComp)
{
	CompList[CompCount++] = pComp;		
	cout << "Component Added. ID: " << pComp->GetID() << " Count: " << CompCount << endl;
}
////////////////////////////////////////////////////////////////////

ActionType ApplicationManager::GetUserAction()
{
	//Call input to get what action is reuired from the user
	return InputInterface->GetUserAction(); 	
}
////////////////////////////////////////////////////////////////////

void ApplicationManager::ExecuteAction(ActionType ActType)
{
	Action* pAct = NULL;
	cout << "Executing Action Type: " << ActType << endl;

	switch (ActType)
	{
		case ADD_AND_GATE_2:
			pAct= new AddANDgate2(this);	
			break;

		case ADD_Label:
			pAct = new AddLabel(this);
			break;

		case EDIT_Label:
			pAct = new EditLabel(this);
			break;

		case DEL:
			pAct = new Delete(this);
			break;

		case SELECT:
			pAct = new Select(this);
			break;

		case ADD_CONNECTION:
			//TODO: Create AddConection Action here
			break;
		
		case SAVE:
			pAct = new SaveAction(this);
			break;

		case LOAD:
			pAct = new LoadAction(this);
			break;

		case SIM_MODE:
			OutputInterface->ClearDesignToolBar();
			OutputInterface->ClearDrawingArea();
			OutputInterface->CreateSimulationToolBar();
			break;

		case DSN_MODE:
			OutputInterface->ClearDesignToolBar();
			OutputInterface->ClearDrawingArea();
			OutputInterface->CreateDesignToolBar();
			UpdateInterface();  // Redraw all components
			break;

		case EXIT:
			///TODO: create ExitAction here
			break;
	}
	if(pAct)
	{
		pAct->Execute();
		delete pAct;
		pAct = NULL;
	}
}
////////////////////////////////////////////////////////////////////

void ApplicationManager::UpdateInterface()
{
	OutputInterface->ClearDrawingArea();
	for(int i=0; i<CompCount; i++)
		CompList[i]->Draw(OutputInterface);

}

////////////////////////////////////////////////////////////////////
Input* ApplicationManager::GetInput()
{
	return InputInterface;
}

////////////////////////////////////////////////////////////////////
Output* ApplicationManager::GetOutput()
{
	return OutputInterface;
}

Component* ApplicationManager::GetComponentByPosition(int x, int y)
{
	cout << "Searching for component at (" << x << ", " << y << ")" << endl;
	for(int i=0; i<CompCount; i++)
	{
		bool isInside = CompList[i]->Inside(x, y);
		cout << "Checking Component " << i << ": Inside(" << x << "," << y << ") = " << isInside << endl;
		if (isInside)
			return CompList[i];
	}
	cout << "No component found." << endl;
	return NULL;
}

void ApplicationManager::DeleteComponent(Component* pComp)
{
	if(!pComp) return;

	// If it's a component (not connection), delete its connections first
	if(dynamic_cast<Connection*>(pComp) == NULL)
	{
		for(int i=0; i<CompCount; i++)
		{
			Connection* pConn = dynamic_cast<Connection*>(CompList[i]);
			if(pConn)
			{
				if (pConn->getSourcePin()->getComponent() == pComp || pConn->getDestPin()->getComponent() == pComp)
				{
					DeleteComponent(pConn);
					i--; // Decrement i because CompList shifted
				}
			}
		}
	}

	// Remove from CompList
	for(int i=0; i<CompCount; i++)
	{
		if(CompList[i] == pComp)
		{
			delete CompList[i];
			CompList[i] = CompList[CompCount-1];
			CompList[CompCount-1] = NULL;
			CompCount--;
			return;
		}
	}
}

////////////////////////////////////////////////////////////////////

void ApplicationManager::SaveCircuit(string filename)
{
	ofstream fout(filename);
	if (!fout.is_open()) return;

	// Count non-connection components
	int nonConnCount = 0;
	for(int i=0; i<CompCount; i++)
	{
		if (dynamic_cast<Connection*>(CompList[i]) == NULL)
			nonConnCount++;
	}

	fout << nonConnCount << endl;

	// Save Components
	for(int i=0; i<CompCount; i++)
	{
		if (dynamic_cast<Connection*>(CompList[i]) == NULL)
			CompList[i]->Save(fout);
	}

	fout << "Connections" << endl;

	// Save Connections
	for(int i=0; i<CompCount; i++)
	{
		if (dynamic_cast<Connection*>(CompList[i]) != NULL)
			CompList[i]->Save(fout);
	}

	fout << "-1" << endl;
	fout.close();
}

void ApplicationManager::LoadCircuit(string filename)
{
	ifstream fin(filename);
	if (!fin.is_open()) return;

	// Clear existing components
	for(int i=0; i<CompCount; i++)
		delete CompList[i];
	CompCount = 0;

	int count;
	fin >> count;

	string type;
	GraphicsInfo GfxInfo; 
	// Initialize GfxInfo with dummy values, Load will overwrite
	GfxInfo.x1 = 0; GfxInfo.y1 = 0; GfxInfo.x2 = 0; GfxInfo.y2 = 0;

	for(int i=0; i<count; i++)
	{
		fin >> type;
		Component* pComp = NULL;
		
		if (type == "AND2")
			pComp = new AND2(GfxInfo, AND2_FANOUT);
		// TODO: Add other component types here
		
		if (pComp)
		{
			pComp->Load(fin);
			AddComponent(pComp);
		}
	}

	fin >> type; // Read "Connections"

	while(fin >> type && type != "-1")
	{
		int srcID = stoi(type);
		int dstID, pinNum;
		fin >> dstID >> pinNum;

		Component* pSrc = NULL;
		Component* pDst = NULL;

		// Find components
		for(int i=0; i<CompCount; i++)
		{
			if(CompList[i]->GetID() == srcID) pSrc = CompList[i];
			if(CompList[i]->GetID() == dstID) pDst = CompList[i];
		}

		if (pSrc && pDst)
		{
			OutputPin* pSrcPin = NULL;
			InputPin* pDstPin = NULL;
			
			// Assuming Source is a Gate for now
			Gate* pSrcGate = dynamic_cast<Gate*>(pSrc);
			if(pSrcGate) pSrcPin = pSrcGate->GetOutputPin();
			
			// Assuming Dest is a Gate
			Gate* pDstGate = dynamic_cast<Gate*>(pDst);
			if(pDstGate) pDstPin = pDstGate->GetInputPin(pinNum - 1); // PinNum is 1-based in file
			
			if(pSrcPin && pDstPin)
			{
				Connection* pConn = new Connection(GfxInfo, pSrcPin, pDstPin);
				AddComponent(pConn);
			}
		}
	}

	fin.close();
}

ApplicationManager::~ApplicationManager()
{
	for(int i=0; i<CompCount; i++)
		delete CompList[i];
	delete OutputInterface;
	delete InputInterface;
	
}