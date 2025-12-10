#ifndef _ADD_LABEL_H
#define _ADD_LABEL_H

#include "Action.h"
#include <string>
using namespace std;

class Component; //Forward declaration

//AddLabel Action: Adds a label to a component or connection
class AddLabel : public Action
{
private:
	int Cx, Cy;	//Click coordinates
	string Label;	//The label text
	Component* pComp;	//Pointer to the component to label

public:
	AddLabel(ApplicationManager *pApp);
	virtual ~AddLabel();

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();

	//Execute action (adds label to component)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();
};

#endif
