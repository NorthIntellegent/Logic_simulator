//#include "Input.h"
#include "Output.h"
#include <iostream>
#include "..\Defs.h"

Input::Input(window* pW)
{
	pWind = pW; //point to the passed window
}

void Input::GetPointClicked(int &x, int &y)
{
	pWind->WaitMouseClick(x, y);	//Wait for mouse click
	cout << "GetPointClicked: (" << x << ", " << y << ")" << endl;
}

string Input::GetString(Output *pOut)
{
	string input = "";
	char c;

	while (true)
	{
		keytype t = pWind->GetKeyPress(c);
		if (t == ASCII)
		{
			if (c == 13) // Enter
				return input;
			else if (c == 8) // Backspace
			{
				if (input.length() > 0)
					input.pop_back();
			}
			else if (c == 27) // Escape
				return "";
			else
				input += c;
			
			pOut->PrintMsg(input);
		}
	}
}

//This function reads the position where the user clicks to determine the desired action
ActionType Input::GetUserAction() const
{	
	int x,y;
	pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click

	if(UI.AppMode == DESIGN )	//application is in design mode
	{
		//[1] If user clicks on the Toolbar
		if ( y >= 0 && y < UI.ToolBarHeight)
		{	
			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = (x / UI.ToolItemWidth);
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			switch (ClickedItemOrder)
			{
			case ITM_AND2: return ADD_AND_GATE_2;
			case ITM_OR2: return ADD_OR_GATE_2;
			case AND3: return ADD_AND_GATE_3;
			case NAND: return ADD_NAND_GATE_2;
			case NOR: return ADD_NOR_GATE_2;
			case NOR3: return ADD_NOR_GATE_3;
			case XOR: return ADD_XOR_GATE_2;
			case XOR3: return 	ADD_XOR_GATE_3;		//Add 3-input XOR gate
			case XNOR: return ADD_XNOR_GATE_2;
			case BUF: return ADD_Buff;
			case INV: return ADD_INV;
			case SWT: return ADD_Switch;
			case BLB: return ADD_LED;
			
			case ITM_LABEL: return ADD_Label;
			case ITM_EDIT: return EDIT_Label;
			case ITM_DELETE: return DEL;
			case ITM_SAVE: return SAVE;
			case ITM_LOAD: return LOAD;
			case ITM_SIM_MODE: return SIM_MODE;

			case ITM_EXIT: return EXIT;	
			
			default: return DSN_TOOL;	//A click on empty place in desgin toolbar
			}
		}
	
		//[2] User clicks on the drawing area
		if ( y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			return SELECT;	//user want to select/unselect a component
		}
		
		//[3] User clicks on the status bar
		return STATUS_BAR;
	}
	else	//Application is in Simulation mode
	{
		//[1] If user clicks on the Toolbar
		if ( y >= 0 && y < UI.ToolBarHeight)
		{	
			//Check which Menu item was clicked
			int ClickedItemOrder = (x / UI.ToolItemWidth);
			
			switch (ClickedItemOrder)
			{
			case ITM_SIM: return SIM_MODE;
			case ITM_TRUTH: return Create_TruthTable;
			case CHK: return Change_Switch;
			case CRCK: return Change_Switch;  //TODO: Add proper circuit check action
			case BAK: return DSN_MODE;  // Back to Design Mode
			
			default: return DSN_TOOL;	//A click on empty place in simulation toolbar
			}
		}
	
		//[2] User clicks on the drawing area
		if ( y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			return SELECT;	//user want to select/unselect a component
		}
		
		//[3] User clicks on the status bar
		return STATUS_BAR;
	}

}


Input::~Input()
{
}
