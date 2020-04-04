#include "stdafx.h"
#include "GuiBaseRect.h"


CGuiBaseRect::CGuiBaseRect()
{
	_Width = _Height= 0;
	_HorizontalPosition = _VerticalPosition = 0;
	_Parent = nullptr;
	_Child = nullptr;
}

CGuiBaseRect::CGuiBaseRect(int argWidth, int argHeight, int argHorizontalPosition, int argVerticalPosition, CGuiBaseRect * argParent)
{
	CGuiBaseRect();

	_Width = argWidth;
	_Height = argHeight;
	_HorizontalPosition = argHorizontalPosition;
	_VerticalPosition = argVerticalPosition;
	_Parent = argParent;
}


CGuiBaseRect::~CGuiBaseRect()
{
}
