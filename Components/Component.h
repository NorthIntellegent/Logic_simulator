#ifndef _COMPONENT_H
#define _COMPONENT_H

#include "..\Defs.h"
#include "..\GUI\Output.h"
#include <fstream>

using namespace std;

class InputPin;

//Base class for classes Gate, Switch, and LED.
class Component
{
private:
	string m_Label;
	int m_ID;
	bool m_Selected; // Selection state
protected:
	GraphicsInfo m_GfxInfo;	//The parameters required to draw a component
public:
	Component(const GraphicsInfo &r_GfxInfo);
	virtual void Operate() = 0;	//Calculates the output according to the inputs
	virtual void Draw(Output* pOut) = 0;	//for each component to Draw itself
	
	virtual void Save(ofstream &fout) = 0;
	virtual void Load(ifstream &fin) = 0;

	virtual int GetOutPinStatus()=0;	//returns status of outputpin if LED, return -1
	virtual int GetInputPinStatus(int n)=0;	//returns status of Inputpin # n if SWITCH, return -1

	virtual void setInputPinStatus(int n, STATUS s)=0;	//set status of Inputpin # n, to be used by connection class.
	
	void SetLabel(string label);
	string GetLabel();
	
	void SetID(int id);
	int GetID();

	virtual bool Inside(int x, int y);
	
	void SetSelected(bool s);
	bool IsSelected() const;

	virtual string GetTypeName() const { return "Component"; } // Returns component type name


	virtual int GetInputPinIndex(InputPin* pPin) { return -1; } // Default implementation returns -1
	
	Component();	
	
	//Destructor must be virtual
	virtual ~Component();
};

#endif
