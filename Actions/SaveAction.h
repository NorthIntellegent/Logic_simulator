#ifndef _SAVE_ACTION_H
#define _SAVE_ACTION_H

#include "Action.h"
#include <string>
using namespace std;

//Save Action: Saves the circuit to a file
class SaveAction : public Action
{
private:
	string Filename;	//The filename to save to

public:
	SaveAction(ApplicationManager *pApp);
	virtual ~SaveAction();

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();

	//Execute action (saves circuit)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();
};

#endif
