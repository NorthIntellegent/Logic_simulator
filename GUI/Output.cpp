#include "Output.h"
#include "..\Defs.h"

Output::Output()
{
	
	//Initialize user interface parameters

	UI.AppMode = DESIGN;	//Design Mode is the startup mode

	//Initilaize interface colors
	UI.DrawColor = BLACK;
	UI.SelectColor = BLUE;
	UI.ConnColor = RED;
	UI.MsgColor = BLUE;
	UI.BkGrndColor = GRAY;
	
	//Create the drawing window
	pWind = CreateWind(UI.width, UI.height, UI.wx, UI.wy);	
	ChangeTitle("Programming Techniques Project");

	CreateDesignToolBar();	//Create the desgin toolbar
	CreateStatusBar();		//Create Status bar

	// Paint the drawing area using the UI background color
	ClearDrawingArea();
}

Input* Output::CreateInput() const
{
	//Create an Input Object & assign it to the Same Window
	Input* pIn = new Input(pWind);
	return pIn;
}


//======================================================================================//
//								Interface Functions										//
//======================================================================================//

window* Output::CreateWind(int wd, int h, int x, int y) const
{
	return new window(wd, h, x, y);
}
//////////////////////////////////////////////////////////////////////////////////
void Output::ChangeTitle(string Title) const
{
	pWind->ChangeTitle(Title);
}
//////////////////////////////////////////////////////////////////////////////////
void Output::CreateStatusBar() const
{
	pWind->SetPen(RED, 3);
	//pWind->DrawLine(0, UI.height - UI.StatusBarHeight, UI.width, UI.height - UI.StatusBarHeight);

	//Draw a rectangle for the status bar
	pWind->SetBrush(UI.BkGrndColor); // Or use a different color like LIGHTGRAY
	pWind->DrawRectangle(0, UI.height - UI.StatusBarHeight, UI.width, UI.height);

	//Draw the separator line
	pWind->DrawLine(0, UI.height - UI.StatusBarHeight, UI.width, UI.height - UI.StatusBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////
void Output::PrintMsg(string msg) const
{
	ClearStatusBar();	//Clear Status bar to print message on it
	// Set the Message offset from the Status Bar
	int MsgX = 25;
	int MsgY = UI.StatusBarHeight - 10;
	
	// Print the Message
    pWind->SetFont(20, BOLD | ITALICIZED, BY_NAME, "Arial"); 
	pWind->SetPen(UI.MsgColor); 
	pWind->DrawString(MsgX, UI.height - MsgY, msg);
}
//////////////////////////////////////////////////////////////////////////////////
void Output::ClearStatusBar()const
{
	// Set the Message offset from the Status Bar
	int MsgX = 25;
	int MsgY = UI.StatusBarHeight - 10;

	//Overwrite using background color to erase the message
	//Overwrite using background color to erase the message
	pWind->SetPen(UI.BkGrndColor);
	pWind->SetBrush(UI.BkGrndColor);
	//Redraw the background of the status bar text area
	pWind->DrawRectangle(MsgX, UI.height - UI.StatusBarHeight + 2, UI.width, UI.height);
}

void Output::ClearDesignToolBar() 
{
	// Draw a rectangle over the toolbar area with the background color
	pWind->SetBrush(UI.BkGrndColor);
	pWind->SetPen(UI.BkGrndColor, 1);

	pWind->DrawRectangle(0, 0, UI.width, UI.ToolBarHeight);
}



//////////////////////////////////////////////////////////////////////////////////////////
//Clears the drawing (design) area
void Output::ClearDrawingArea() const
{
	// Use UI.BkGrndColor so the background follows the UI setting
	pWind->SetPen(UI.BkGrndColor, 1);
	pWind->SetBrush(UI.BkGrndColor);
	pWind->DrawRectangle(0, UI.ToolBarHeight, UI.width, UI.height - UI.StatusBarHeight);
	
}
//////////////////////////////////////////////////////////////////////////////////////////
//Draws the menu (toolbar) in the Design mode
void Output::CreateDesignToolBar() const
{
	UI.AppMode = DESIGN;	//Design Mode

	//You can draw the tool bar icons in any way you want.

	//First prepare List of images for each menu item
	string MenuItemImages[ITM_DSN_CNT];
	MenuItemImages[ITM_AND2] = "images\\Menu\\Menu_AND2.jpg";
	MenuItemImages[ITM_OR2]  = "images\\Menu\\Menu_OR2.jpg";
	MenuItemImages[NAND] = "images\\Menu\\NAND.jpg";
	MenuItemImages[NOR] = "images\\Menu\\NOR.jpg";
	MenuItemImages[XOR] = "images\\Menu\\XOR.jpg";
	MenuItemImages[XNOR] = "images\\Menu\\XNOR.jpg";
	MenuItemImages[AND3] = "images\\Menu\\AND3.jpg";
	MenuItemImages[NOR3] = "images\\Menu\\NOR3.jpg";
	MenuItemImages[XOR3] = "images\\Menu\\XOR3.jpg";
	MenuItemImages[BUF] = "images\\Menu\\BUF.jpg";
	MenuItemImages[INV] = "images\\Menu\\INV.jpg";
	MenuItemImages[SWT] = "images\\Menu\\SWT.jpg";
	MenuItemImages[BLB] = "images\\Menu\\BLB.jpg";
	
	MenuItemImages[ITM_LABEL] = "images\\Menu\\ITM_LABEL.jpg";
	MenuItemImages[ITM_EDIT] = "images\\Menu\\ITM_EDIT.jpg";
	MenuItemImages[ITM_DELETE] = "images\\Menu\\ITM_DELETE.jpg";
	MenuItemImages[ITM_SAVE] = "images\\Menu\\ITM_SAVE.jpg";
	MenuItemImages[ITM_LOAD] = "images\\Menu\\ITM_LOAD.jpg";

	MenuItemImages[ITM_EXIT] = "images\\Menu\\Menu_Exit.jpg";

	//TODO: Prepare image for each menu item and add it to the list

	//Draw menu item one image at a time
	int iconW = UI.AND2_Width;
	int iconH = UI.AND2_Height;

	for (int i = 0; i < ITM_DSN_CNT; ++i)
	{
	    int slotX = i * UI.ToolItemWidth;
	    int drawX = slotX + (UI.ToolItemWidth - iconW) / 2;   // center in slot
	    int drawY = (UI.ToolBarHeight - iconH) / 2;           // center vertically
	    pWind->DrawImage(MenuItemImages[i], drawX, drawY, iconW, iconH);
	}


	//Draw a line under the toolbar
	pWind->SetPen(BLUE,2);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);	

}
//////////////////////////////////////////////////////////////////////////////////////////
//Draws the menu (toolbar) in the simulation mode

void Output::SimulationMode(Output &out)
{
	Input* pIn = out.CreateInput();

	int x, y;
	pIn->GetPointClicked(x, y);

	if ((x > 786 && x < 834) && (y > 10 && y < 58))
	{
		out.ClearDesignToolBar();
		out.ClearDrawingArea();
		out.CreateSimulationToolBar();
	}
}




void Output::CreateSimulationToolBar() const
{
	UI.AppMode = SIMULATION;	//Simulation Mode

	//TODO: Write code to draw the simualtion toolbar (similar to that of design toolbar drawing)
	string MenuItemImages[ITM_SIM_CNT]; 
	MenuItemImages[CHK] = "images\\Menu\\CHK.jpg";
	MenuItemImages[ITM_TRUTH] = "images\\Menu\\ITM_TRUTH.jpg";
	MenuItemImages[ITM_SIM] = "images\\Menu\\ITM_SIM.jpg";
	MenuItemImages[CRCK] = "images\\Menu\\CRCK.jpg";
	MenuItemImages[BAK] = "images\\Menu\\BAK.jpg";
	int iconW = UI.AND2_Width;
	int iconH = UI.AND2_Height;

	for (int i = 0; i < ITM_SIM_CNT; ++i)
	{
		int slotX = i * UI.ToolItemWidth;
		int drawX = slotX + (UI.ToolItemWidth - iconW) / 2;   // center in slot
		int drawY = (UI.ToolBarHeight - iconH) / 2;           // center vertically
		pWind->DrawImage(MenuItemImages[i], drawX, drawY, iconW, iconH);
	}


	//Draw a line under the toolbar
	pWind->SetPen(BLUE, 2);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);

}


//======================================================================================//
//								Components Drawing Functions							//
//======================================================================================//

void Output::DrawAND2(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if(selected)	//use image in the highlighted case
		GateImage="Images\\Gates\\AND2_hi.jpg";
	else  
		GateImage = "Images\\Gates\\AND2.jpg";

	//Draw AND2 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by AND2 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}

//TODO: Add similar functions to draw all components

void Output::DrawNAND2(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\NAND_hi.jpg";
	else
		GateImage = "Images\\Gates\\NAND.jpg";

	//Draw AND2 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by AND2 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}

void Output::DrawOR2(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\OR2_hi.jpg";
	else
		GateImage = "Images\\Gates\\OR2.jpg";

	//Draw AND2 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by AND2 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}

void Output::DrawNOR2(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\NOR_hi.jpg";
	else
		GateImage = "Images\\Gates\\NOR.jpg";

	//Draw AND2 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by AND2 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}

void Output::DrawXOR2(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\XOR_hi.jpg";
	else
		GateImage = "Images\\Gates\\XOR.jpg";

	//Draw AND2 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by AND2 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}

void Output::DrawXNOR2(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\XNOR_hi.jpg";
	else
		GateImage = "Images\\Gates\\XNOR.jpg";

	//Draw AND2 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by AND2 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}

void Output::DrawBUFFER(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\BUF_hi.jpg";
	else
		GateImage = "Images\\Gates\\BUF.jpg";

	//Draw AND2 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by AND2 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}

void Output::DrawINVERTER(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\INV_hi.jpg";
	else
		GateImage = "Images\\Gates\\INV.jpg";

	//Draw AND2 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by AND2 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}

void Output::DrawAND3(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\AND3_hi.jpg";
	else
		GateImage = "Images\\Gates\\AND3.jpg";

	//Draw AND2 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by AND2 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}

void Output::DrawNOR3(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\NOR3_hi.jpg";
	else
		GateImage = "Images\\Gates\\NOR3.jpg";

	//Draw AND2 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by AND2 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}

void Output::DrawXOR3(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\XOR3_hi.jpg";
	else
		GateImage = "Images\\Gates\\XOR3.jpg";

	//Draw AND2 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by AND2 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}

void Output::DrawSWITCH(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\SWT_hi.jpg";
	else
		GateImage = "Images\\Gates\\SWT.jpg";

	//Draw AND2 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by AND2 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}

void Output::DrawLED(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\BLB_hi.jpg";
	else
		GateImage = "Images\\Gates\\BLB.jpg";

	//Draw AND2 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by AND2 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}

void Output::DrawConnection(GraphicsInfo r_GfxInfo, bool selected) const
{

	if (selected) {
		pWind->SetPen(UI.SelectColor, 3);
	}
	else
	{
		pWind->SetPen(UI.ConnColor, 2);
	}

	//Draw connection (orthogonal)
	//1. Horizontal line from x1 to mid x
	//2. Vertical line from y1 to y2 at mid x
	//3. Horizontal line from mid x to x2
	
	int midX = (r_GfxInfo.x1 + r_GfxInfo.x2) / 2;
	
	pWind->DrawLine(r_GfxInfo.x1, r_GfxInfo.y1, midX, r_GfxInfo.y1);
	pWind->DrawLine(midX, r_GfxInfo.y1, midX, r_GfxInfo.y2);
	pWind->DrawLine(midX, r_GfxInfo.y2, r_GfxInfo.x2, r_GfxInfo.y2);
}

 
Output::~Output()
{
	delete pWind;
}
