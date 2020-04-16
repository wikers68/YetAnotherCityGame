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

CGuiBaseRect::CGuiBaseRect(std::string argWidth, std::string  argHeight, int argHorizontalPosition, int argVerticalPosition)
{
	commandWidthString = argWidth;
	_Width = -1;  

	commandHeightString = argHeight;
	_Height = -1;
	
	_HorizontalPosition = argHorizontalPosition;
	_VerticalPosition = argVerticalPosition;
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

	if (_Parent != nullptr)
	{
		if (_HorizontalPosition >= 0)
		{
			_AbsoluteHorizontalPosition = _Parent->_AbsoluteHorizontalPosition + _HorizontalPosition;
			_AbsoluteVerticalPosition = _Parent->_AbsoluteVerticalPosition + _VerticalPosition;
		}
		else
		{
			switch (_HorizontalPosition)
			{
			default:
				_AbsoluteHorizontalPosition = _Parent->_AbsoluteHorizontalPosition;
				_AbsoluteVerticalPosition = _Parent->_AbsoluteVerticalPosition + _VerticalPosition;;
				break;
			case HORIZONTAL_CENTER:
				_AbsoluteHorizontalPosition = _Parent->_AbsoluteHorizontalPosition + int( (float)((_Parent->_Width - this->_Width)) / 2.0f);
				_AbsoluteVerticalPosition = _Parent->_AbsoluteVerticalPosition + _VerticalPosition;
				break;
			case HORIZONTAL_LEFT:
				_AbsoluteHorizontalPosition = _Parent->_AbsoluteHorizontalPosition;
				_AbsoluteVerticalPosition = _Parent->_AbsoluteVerticalPosition + _VerticalPosition;;
				break;
			case HORIZONTAL_RIGHT:
				_AbsoluteHorizontalPosition = _Parent->_AbsoluteHorizontalPosition + (_Parent->_Width - this->_Width);
				_AbsoluteVerticalPosition = _Parent->_AbsoluteVerticalPosition + _VerticalPosition;
				break;
			}
		}
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
		if (SizeHasBeenCalculated)
		{
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
	if (SizeHasBeenCalculated)
	{
		return _Height;
	}
	else
	{
		CalculateSize();
		
		getHeight();
	}
}

int CGuiBaseRect::getWidth(void)
{
	if (SizeHasBeenCalculated)
	{
		return _Width;
	}
	else
	{
		CalculateSize();

		getWidth();
	}
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

void CGuiBaseRect::SetCommandString(std::string command, Translate_Size ts)
{
	switch (ts)
	{
		default:break;
		case Translate_Size::WIDTH:
			commandWidthString = command;
			break;
		case Translate_Size::HEIGHT:
			commandHeightString = command;
			break;
	}

	Reset_HasBeenCalculated();
}

int CGuiBaseRect::TranslateStringToSize(std::string arg, Translate_Size ts)
{
	int argLength = arg.length();

	if (argLength > 0)
	{
		char lastCharacter = arg[argLength - 1];

		if (lastCharacter == 'p' || lastCharacter == 'P')
		{
			std::string pixelSize = arg;
			pixelSize.resize(argLength - 1);

			return std::atoi(pixelSize.c_str());
		}

		if (lastCharacter == '%' || lastCharacter == '%')
		{
			std::string pourcentSize = arg;
			pourcentSize.resize(argLength - 1);
			float pourcentSizeF = 0.01 *  std::atof(pourcentSize.c_str());

			if (_Parent)
			{
				if (ts == WIDTH)
				{
					float fWidth = (float)_Parent->_Width * pourcentSizeF;
					return (int)fWidth;
				}
				else if(ts == HEIGHT)
				{
					float fHeight = (float)_Parent->_Height* pourcentSizeF;
					return (int)fHeight;
				}
				return 0;
			}
			
			return 0;
		}

	}

	return 0;
}

void CGuiBaseRect::CalculateSize(void)
{
	_Width = TranslateStringToSize(commandWidthString,WIDTH);
	_Height = TranslateStringToSize(commandHeightString, HEIGHT);

	SizeHasBeenCalculated = true;
}
