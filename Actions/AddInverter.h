#ifndef _ADD_INVERTER_H
#define _ADD_INVERTER_H

#include "action.h"
#include "..\Components\INVERTER.h"

class AddInverter :	public Action
{
private:
	int Cx, Cy;
	int x1, y1, x2, y2;
public:
	AddInverter(ApplicationManager *pApp);
	virtual ~AddInverter(void);

	virtual void ReadActionParameters();
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();

};

#endif
