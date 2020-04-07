#include "stdafx.h"
#include "GuiBaseRect.h"


CGuiBaseRect::CGuiBaseRect()
{
	_Width = _Height = 0;
	_HorizontalPosition = _VerticalPosition = 0;
	_Parent = nullptr;
	_Child = nullptr;
	_isVisible = true;

	//OnClick_CallBackFunction = IsOver_CallBackFunction = IsLeaving_CallBackFunction = nullptr;
}

CGuiBaseRect::CGuiBaseRect(int argWidth, int argHeight, int argHorizontalPosition, int argVerticalPosition)
{
	_Width = argWidth;
	_Height = argHeight;
	_HorizontalPosition = argHorizontalPosition;
	_VerticalPosition = argVerticalPosition;
	_Parent = nullptr;
	_Child = nullptr;
	_isVisible = true;

	//update absolute position in case where a parent is attached
	Update();
}


CGuiBaseRect::~CGuiBaseRect()
{
}

void CGuiBaseRect::Hide(void)
{
	this->_isVisible = false;
}

void CGuiBaseRect::Show(void)
{
	this->_isVisible = true;
}

bool CGuiBaseRect::IsVisible(void)
{
	return _isVisible;
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

void CGuiBaseRect::DrawChild(void)
{
	if (_Child)
	{
		std::list<CGuiBaseRect*>::iterator it = _Child->begin();

		for (it = _Child->begin(); it != _Child->end(); it++)
		{
			(*it)->Draw();
		}
	}
}
void CGuiBaseRect::Draw(float delta_t)
{
	if (_isVisible)
	{
		DrawLocal(delta_t);
		DrawChild();
	}
}


bool CGuiBaseRect::PointerIsInside_Rect(int x, int y)
{
	if (x > this->_AbsoluteHorizontalPosition && x <= (_AbsoluteHorizontalPosition + _Width))
	{
		if (y > this->_AbsoluteVerticalPosition && y <= (_AbsoluteVerticalPosition + _Height))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

void CGuiBaseRect::Generate_Mousse_Action(SDL_Event evt)
{
	switch (evt.type)
	{
	default: break;
	case SDL_MOUSEMOTION:
		CheckMouseIsOver(evt);
		CheckMouseIsLeaving(evt);
		break;
	case SDL_MOUSEBUTTONDOWN:
		CheckMouseClick(evt);
		break;
	}
}