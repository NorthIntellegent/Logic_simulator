#ifndef _DELETE_H
#define _DELETE_H

#include "Action.h"
#include <string>
using namespace std;

class Component; //Forward declaration

//Delete Action: Deletes a component or connection
class Delete : public Action
{
private:
	int Cx, Cy;	//Click coordinates
	Component* pComp;	//Pointer to the component to delete

public:
	Delete(ApplicationManager *pApp);
	virtual ~Delete();

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();

	//Execute action (deletes component)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();
};

#endif
