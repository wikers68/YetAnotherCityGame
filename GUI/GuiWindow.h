#pragma once

#include "CommonGUIheader.h"

class CGuiWindow : public CGui2DRect
{
public:
	CGuiWindow(Widget_Style style);
	~CGuiWindow();

	void SetTitle(std::wstring title);

	void wAddChild(CGuiBaseRect * child);

	//void ShowCloseButton(bool display);

private:
	CGui2DRect *leftBorder;
	CGui2DRect *rightBorder;
	CGui2DRect *topBorder;
	CGui2DRect *bottomBorder;

	CGui2DRect *titleBackground;

	CDisplayText *titre;

	/*
	*	The free rectangle area where we can add child
	*/
	CGui2DRect *freeArea;
};

