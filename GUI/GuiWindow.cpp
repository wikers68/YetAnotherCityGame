#include "stdafx.h"
#include "GuiWindow.h"


CGuiWindow::CGuiWindow(std::string argWidth, std::string  argHeight, int argHorizontalPosition, int argVerticalPosition):CGui2DRect(argWidth ,argHeight ,argHorizontalPosition, argVerticalPosition)
{
	int borderThickness = 5;
	std::string borderThickness_Command = ConvertIntToCommandeSring(borderThickness, "p");

	int titleBackgroundHeight = 50;
	std::string titleBackgroundHeightCommand = ConvertIntToCommandeSring(titleBackgroundHeight, "p");

	leftBorder = new CGui2DRect("5p", "100%", HORIZONTAL_LEFT, 0);
	leftBorder->SetBackGroundColor(WHITE);

	rightBorder = new CGui2DRect("5p", "100%", HORIZONTAL_RIGHT, 0);
	rightBorder->SetBackGroundColor(WHITE);

	topBorder = new CGui2DRect("100%", "5p", HORIZONTAL_RIGHT, 0);
	topBorder->SetBackGroundColor(WHITE);

	bottomBorder = new CGui2DRect("100%", "5p", HORIZONTAL_RIGHT, VERTICAL_BOTTOM);
	bottomBorder->SetBackGroundColor(WHITE);

	titleBackground = new CGui2DRect("100%", titleBackgroundHeightCommand, HORIZONTAL_LEFT, VERTICAL_TOP);
	titleBackground->SetBackGroundColor(0.45f, 0.45f, 0.45f, 1.0f);
	this->AddChild(titleBackground);

	titre = new CDisplayText("100%", "30p", HORIZONTAL_CENTER, VERTICAL_CENTER);
	titleBackground->AddChild(titre);

	this->AddChild(leftBorder);
	this->AddChild(rightBorder);
	this->AddChild(bottomBorder);
	this->AddChild(topBorder);

	/*
	*	Set up the area in which we will add child later
	*/
	int freeArea_Vertical_Position = titleBackgroundHeight;
	std::string fvp = ConvertIntToCommandeSring(freeArea_Vertical_Position, "p");

	int freeAreaWidth = this->_Width  - 2 * borderThickness;
	std::string fw = ConvertIntToCommandeSring(freeAreaWidth, "p");

	int freeAreaHeight = this->_Height - titleBackgroundHeight - 1 * borderThickness;
	std::string fh = ConvertIntToCommandeSring(freeAreaHeight, "p");

	freeArea = new CGui2DRect(fw, fh, HORIZONTAL_CENTER, titleBackgroundHeight);
	freeArea->SetBackGroundColor(0.4f, 0.0f, 0.5f);

	this->AddChild(freeArea);

}


CGuiWindow::~CGuiWindow()
{
}

void CGuiWindow::SetTitle(std::wstring title)
{
	titre->SetText(title);
}

void CGuiWindow::wAddChild(CGuiBaseRect * child)
{
	freeArea->AddChild(child);
}

/*void CGuiWindow::ShowCloseButton(bool display)
{
}*/
