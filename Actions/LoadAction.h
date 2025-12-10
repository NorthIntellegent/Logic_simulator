#ifndef _LOAD_ACTION_H
#define _LOAD_ACTION_H

#include "Action.h"
#include <string>
using namespace std;

//Load Action: Loads a circuit from a file
class LoadAction : public Action
{
private:
	string Filename;	//The filename to load from

public:
	LoadAction(ApplicationManager *pApp);
	virtual ~LoadAction();

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();

	//Execute action (loads circuit)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();
};

#endif
