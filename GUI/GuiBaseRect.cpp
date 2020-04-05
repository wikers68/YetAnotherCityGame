#include "stdafx.h"
#include "GuiBaseRect.h"


CGuiBaseRect::CGuiBaseRect()
{
	_Width = _Height= 0;
	_HorizontalPosition = _VerticalPosition = 0;
	_Parent = nullptr;
	_Child = nullptr;
}

CGuiBaseRect::CGuiBaseRect(int argWidth, int argHeight, int argHorizontalPosition, int argVerticalPosition)
{
	_Width = argWidth;
	_Height = argHeight;
	_HorizontalPosition = argHorizontalPosition;
	_VerticalPosition = argVerticalPosition;
	_Parent = nullptr;
	_Child = nullptr;

	//update absolute position in case where a parent is attached
	Update();
}


CGuiBaseRect::~CGuiBaseRect()
{
}

void CGuiBaseRect::AddChild(CGuiBaseRect *argChild)
{
	if (_Child == nullptr)
	{
		_Child = new std::list<CGuiBaseRect*>();
	}

	_Child->push_back(argChild);

	argChild->_Parent = this;

	argChild->Update();
}

void CGuiBaseRect::Update(void)
{
	if (_Parent != nullptr)
	{
		_AbsoluteHorizontalPosition = _Parent->_AbsoluteHorizontalPosition + _HorizontalPosition;
		_AbsoluteVerticalPosition = _Parent->_AbsoluteVerticalPosition + _VerticalPosition;
	}
	else
	{
		//if no parent is linked to the widget, the position on screen = the relative position

		_AbsoluteHorizontalPosition = _HorizontalPosition;
		_AbsoluteVerticalPosition = _VerticalPosition;
	}


	//then we update children
	if (_Child)
	{
		std::list<CGuiBaseRect*>::iterator it;

		for (it = _Child->begin(); it != _Child->end(); it++)
		{
			(*it)->Update();
		}
	}
}