#ifndef _ADD_LED_H
#define _ADD_LED_H

#include "action.h"
#include "..\Components\LED.h"

class AddLED :	public Action
{
private:
	int Cx, Cy;
	int x1, y1, x2, y2;
public:
	AddLED(ApplicationManager *pApp);
	virtual ~AddLED(void);

	virtual void ReadActionParameters();
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();

};

#endif
