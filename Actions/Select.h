#ifndef _SELECT_ACTION_H
#define _SELECT_ACTION_H

#include "Action.h"
#include <string>
using namespace std;

class Component; //Forward declaration

//Select Action: Selects/deselects a component for highlighting
class Select : public Action
{
private:
	int Cx, Cy;	//Click coordinates
	Component* pSelectedComp;	//Pointer to the selected component

public:
	Select(ApplicationManager *pApp);
	virtual ~Select();

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();

	//Execute action (selects/deselects component)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();
};

#endif
