#ifndef _EDIT_LABEL_H
#define _EDIT_LABEL_H

#include "Action.h"
#include <string>
using namespace std;

class Component; //Forward declaration

//EditLabel Action: Edits an existing label on a component
class EditLabel : public Action
{
private:
	int Cx, Cy;	//Click coordinates
	string OldLabel;	//The old label
	string NewLabel;	//The new label text
	Component* pComp;	//Pointer to the component to edit

public:
	EditLabel(ApplicationManager *pApp);
	virtual ~EditLabel();

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();

	//Execute action (edits label)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();
};

#endif
