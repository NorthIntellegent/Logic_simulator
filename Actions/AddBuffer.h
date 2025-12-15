#ifndef _ADD_BUFFER_H
#define _ADD_BUFFER_H

#include "action.h"
#include "..\Components\BUFFER.h"

class AddBuffer :	public Action
{
private:
	int Cx, Cy;
	int x1, y1, x2, y2;
public:
	AddBuffer(ApplicationManager *pApp);
	virtual ~AddBuffer(void);

	virtual void ReadActionParameters();
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();

};

#endif
