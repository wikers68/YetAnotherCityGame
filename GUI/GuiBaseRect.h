#pragma once

/*
*	Base Class to manage rectangular GUI element such as, window, button...
*/

#include <list>

class CGuiBaseRect
{
public:
	CGuiBaseRect();
	CGuiBaseRect(int argWidth,int argHeight, int argHorizontalPosition, int argVerticalPosition, CGuiBaseRect *argParent = nullptr );

	~CGuiBaseRect();

	int _Width;
	int _Height;

	int _HorizontalPosition;
	int _VerticalPosition;

	CGuiBaseRect *_Parent;

	//link to other GuiElement linked to the current CGuiBaseRect 
	std::list<CGuiBaseRect*> *_Child;
};

