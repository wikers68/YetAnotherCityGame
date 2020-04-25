#include "stdafx.h"
#include "GuiWindow.h"


CGuiWindow::CGuiWindow(Widget_Style style):CGui2DRect(style)
{
	int borderThickness = 5;

	Widget_Style wsVerticalBorder;
	wsVerticalBorder.hPosition = HORIZONTAL_LEFT;
	wsVerticalBorder.vPosition = VERTICAL_TOP;
	wsVerticalBorder.hSize.size = borderThickness;
	wsVerticalBorder.hSize.AbsOrRel = ABS_REL::_ABSOLUTE;
	wsVerticalBorder.vSize.size = 100;
	wsVerticalBorder.vSize.AbsOrRel = ABS_REL::_RELATIVE;
	wsVerticalBorder.vSize.relTo = SIZE_RELATIVE_TO::PARENT;

	Widget_Style wsHorizontalBorder;
	wsHorizontalBorder.hPosition = HORIZONTAL_LEFT;
	wsHorizontalBorder.vSize.size = borderThickness;
	wsHorizontalBorder.vSize.AbsOrRel = ABS_REL::_ABSOLUTE;
	wsHorizontalBorder.hSize.size = 100;
	wsHorizontalBorder.hSize.AbsOrRel = ABS_REL::_RELATIVE;
	wsHorizontalBorder.hSize.relTo = SIZE_RELATIVE_TO::PARENT;


	leftBorder = new CGui2DRect(wsVerticalBorder);
	leftBorder->SetBackGroundColor(WHITE);
	
	wsVerticalBorder.hPosition = HORIZONTAL_RIGHT;
	rightBorder = new CGui2DRect(wsVerticalBorder);
	rightBorder->SetBackGroundColor(WHITE);

	wsHorizontalBorder.vPosition = VERTICAL_TOP;
	topBorder = new CGui2DRect(wsHorizontalBorder);
	topBorder->SetBackGroundColor(WHITE);

	wsHorizontalBorder.vPosition = VERTICAL_BOTTOM;
	bottomBorder = new CGui2DRect(wsHorizontalBorder);
	bottomBorder->SetBackGroundColor(WHITE);

	Widget_Style wstitleBackground;
	wstitleBackground.hPosition = 0;
	wstitleBackground.vPosition = 0;
	wstitleBackground.vSize.size = 50;
	wstitleBackground.vSize.AbsOrRel = ABS_REL::_ABSOLUTE;
	wstitleBackground.hSize.size = 100;
	wstitleBackground.hSize.AbsOrRel = ABS_REL::_RELATIVE;
	wstitleBackground.hSize.relTo = SIZE_RELATIVE_TO::PARENT;

	titleBackground = new CGui2DRect(wstitleBackground);
	titleBackground->SetBackGroundColor(0.45f, 0.45f, 0.45f, 1.0f);
	this->AddChild(titleBackground);

	Widget_Style wsTitre;
	wsTitre.hPosition = HORIZONTAL_CENTER;
	wsTitre.vPosition = VERTICAL_CENTER;
	wsTitre.vSize.size = wstitleBackground.vSize.size  - 10;
	wsTitre.vSize.AbsOrRel = ABS_REL::_ABSOLUTE;
	wsTitre.hSize.size = 100;
	wsTitre.hSize.AbsOrRel = ABS_REL::_RELATIVE;
	wsTitre.hSize.relTo = SIZE_RELATIVE_TO::PARENT;

	titre = new CDisplayText(wsTitre);
	titleBackground->AddChild(titre);

	this->AddChild(leftBorder);
	this->AddChild(rightBorder);
	this->AddChild(bottomBorder);
	this->AddChild(topBorder);

	/*
	*	Set up the area in which we will add child later
	*/

	Widget_Style wsFreeArea;
	wsFreeArea.hPosition = borderThickness;
	wsFreeArea.vPosition = wstitleBackground.vSize.size;
	wsFreeArea.hSize.AbsOrRel = ABS_REL::_ABSOLUTE;
	wsFreeArea.hSize.size = this->_Width - 2 * borderThickness;
	wsFreeArea.vSize.AbsOrRel = ABS_REL::_ABSOLUTE;
	wsFreeArea.vSize.size = this->_Height - wstitleBackground.vSize.size - 1 * borderThickness;

	freeArea = new CGui2DRect(wsFreeArea);
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
