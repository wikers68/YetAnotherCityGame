#include "stdafx.h"
#include "GuiBaseRect.h"


CGuiBaseRect::CGuiBaseRect()
{
	_Width = _Height = 0;
	_HorizontalPosition = _VerticalPosition = 0;

	_Parent = nullptr;
	_Child = nullptr;
	_isVisible = true;
	commandWidthString = "";

	//OnClick_CallBackFunction = IsOver_CallBackFunction = IsLeaving_CallBackFunction = nullptr;
}

CGuiBaseRect::CGuiBaseRect(Widget_Style style)
{
	this->style = style;
	
	_Width = -1;

	_Height = -1;

	_HorizontalPosition = 0;
	_VerticalPosition = 0;
	_Parent = nullptr;
	_Child = nullptr;
	_isVisible = true;

	SizeHasBeenCalculated = false;

	Update();
}


CGuiBaseRect::~CGuiBaseRect()
{
	if (_Child) _Child->clear();
	delete _Child;
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
	argChild->Reset_HasBeenCalculated();

	argChild->Update();
}

void CGuiBaseRect::Update(void)
{
	if (!SizeHasBeenCalculated)
	{
		CalculateSize();
	}

	int Horizontal_Offset = 0;
	int Vertical_Offset = 0;

	if (_Parent != nullptr)
	{
		Calc_PositionWithParent();
	}
	else
	{
		Calc_PositionNoParent();
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
		if (SizeHasBeenCalculated)
		{
			/*
			*	Draw GUI Over others elements
			*/
			if (glIsEnabled(GL_DEPTH_TEST))
			{
				glDisable(GL_DEPTH_TEST);
			}

			DrawLocal(delta_t);
			DrawChild();
		}
		else
		{
			/*
			*	Update element size;
			*/
			CalculateSize();
		}
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

int CGuiBaseRect::getHeight(void)
{
	/*
	*	2020/04/24 : change to run update calculation each frame. 
	*/
	SizeHasBeenCalculated = false;
	CalculateSize();
	return _Height;

	/*if (SizeHasBeenCalculated)
	{
		return _Height;
	}
	else
	{
		CalculateSize();

		getHeight();
	}*/
}

int CGuiBaseRect::getWidth(void)
{
	SizeHasBeenCalculated = false;
	CalculateSize();
	return _Width;

	/*if (SizeHasBeenCalculated)
	{
		return _Width;
	}
	else
	{
		CalculateSize();

		getWidth();
	}*/
}

void CGuiBaseRect::Reset_HasBeenCalculated(void)
{
	SizeHasBeenCalculated = false;

	if (_Child)
	{
		std::list<CGuiBaseRect*>::iterator it;

		for (it = _Child->begin(); it != _Child->end(); it++)
		{
			(*it)->Reset_HasBeenCalculated();
		}
	}
}


void CGuiBaseRect::CalculateSize(void)
{

	switch (style.hSize.AbsOrRel)
	{
	case ABS_REL::_ABSOLUTE:
		_Width = style.hSize.size;
		break;
	case ABS_REL::_RELATIVE:
		if (style.hSize.relTo == SIZE_RELATIVE_TO::PARENT)
		{
			if (_Parent)
			{
				_Width = (int)( style.hSize.size / 100.0f * (float)this->_Parent->getWidth());
			}
		}
		if (style.hSize.relTo == SIZE_RELATIVE_TO::CHILDREN)
		{

		}
		break;
	}

	switch (style.vSize.AbsOrRel)
	{
	case ABS_REL::_ABSOLUTE:
		_Height = style.vSize.size;
		break;
	case ABS_REL::_RELATIVE:
		if (style.vSize.relTo == SIZE_RELATIVE_TO::PARENT)
		{
			if (_Parent) _Height = style.vSize.size  / 100.0f * (float)this->_Parent->getHeight();
		}
		if (style.vSize.relTo == SIZE_RELATIVE_TO::CHILDREN)
		{

		}
		break;
	}

	SizeHasBeenCalculated = true;
}

void CGuiBaseRect::Calc_PositionNoParent(void)
{
	int ScreenWidth = COption::getInstance().Get_Horizontal_Resolution();
	int screenHeight = COption::getInstance().Get_Vertical_Resolution();

	/*
		*	Horizontal position calculation
		*/
	switch (style.hPosition)
	{
	default:
		_AbsoluteHorizontalPosition = style.hPosition;
		break;
	case HORIZONTAL_CENTER:
		_AbsoluteHorizontalPosition = (ScreenWidth - this->getWidth()) / 2.0;
		break;
	case HORIZONTAL_LEFT:
		_AbsoluteHorizontalPosition = 0;
		break;
	case HORIZONTAL_RIGHT:
		_AbsoluteHorizontalPosition = ScreenWidth - this->getWidth();
		break;
	}

	/*
	*	Vertical position calculation
	*/
	switch (style.vPosition)
	{
	default:
		_AbsoluteVerticalPosition = style.vPosition;
		break;
	case VERTICAL_TOP:
		_AbsoluteVerticalPosition = style.vPosition;
		break;
	case VERTICAL_CENTER:
		_AbsoluteVerticalPosition = (screenHeight - this->getHeight()) / 2;
		break;
	case VERTICAL_BOTTOM:
		_AbsoluteVerticalPosition = screenHeight - this->getHeight();
		break;
	}
}

void CGuiBaseRect::Calc_PositionWithParent(void)
{
	switch (style.hPosition)
	{
	default:
		_AbsoluteHorizontalPosition = _Parent->_AbsoluteHorizontalPosition + style.hPosition;
		break;
	case HORIZONTAL_CENTER:
		_AbsoluteHorizontalPosition = _Parent->_AbsoluteHorizontalPosition + int((float)((_Parent->getWidth() - this->getWidth())) / 2.0f);
		break;
	case HORIZONTAL_LEFT:
		_AbsoluteHorizontalPosition = _Parent->_AbsoluteHorizontalPosition;
		break;
	case HORIZONTAL_RIGHT:
		_AbsoluteHorizontalPosition = _Parent->_AbsoluteHorizontalPosition + (_Parent->getWidth() - this->getWidth());
		break;
	}

	switch (style.vPosition)
	{
	default:
		_AbsoluteVerticalPosition = _Parent->_AbsoluteVerticalPosition + style.vPosition;
		break;
	case VERTICAL_TOP:
		_AbsoluteVerticalPosition = _Parent->_AbsoluteVerticalPosition + style.vPosition;
		break;
	case VERTICAL_CENTER:
		_AbsoluteVerticalPosition = _Parent->_AbsoluteVerticalPosition + (_Parent->getHeight() - this->getHeight()) /2 ;
		break;
	case VERTICAL_BOTTOM:
		_AbsoluteVerticalPosition = _Parent->_AbsoluteVerticalPosition + _Parent->getHeight() - this->getHeight();
		break;
	}
}
