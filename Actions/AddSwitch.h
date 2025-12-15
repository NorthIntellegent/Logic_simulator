#ifndef _ADD_SWITCH_H
#define _ADD_SWITCH_H

#include "action.h"
#include "..\Components\SWITCH.h"

class AddSwitch :	public Action
{
private:
	int Cx, Cy;
	int x1, y1, x2, y2;
public:
	AddSwitch(ApplicationManager *pApp);
	virtual ~AddSwitch(void);

	virtual void ReadActionParameters();
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();

};

#endif
