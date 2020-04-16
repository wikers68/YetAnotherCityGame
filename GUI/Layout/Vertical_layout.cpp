#include "stdafx.h"
#include "Vertical_layout.h"


CVertical_layout::CVertical_layout(std::string argWidth, std::string  argHeight, int argHorizontalPosition, int argVerticalPosition,int spaceBetweenChild) : CGuiBaseRect(argWidth, argHeight, argHorizontalPosition, argVerticalPosition)
{
	Space = spaceBetweenChild;
}


CVertical_layout::~CVertical_layout()
{
}

void CVertical_layout::AddChild(CGuiBaseRect * argChild)
{
	CGuiBaseRect::AddChild(argChild);
	Update();
}

void CVertical_layout::Update(void)
{
	if (_Child)
	{
		int NumberOfChild = _Child->size();

		if (NumberOfChild > 0)
		{
			int numberOfSpace = NumberOfChild + 1;

			int TotalSpaceHeight = numberOfSpace * Space;

			int RemainingHeight = this->getHeight() - TotalSpaceHeight;

			int Child_Height = RemainingHeight / NumberOfChild;

			std::list<CGuiBaseRect*>::iterator it;
			int c = 0;

			for (it = _Child->begin(); it != _Child->end(); it++)
			{
				(*it)->SetCommandString(std::to_string(Child_Height).append("p"),Translate_Size::HEIGHT);
				(*it)->_VerticalPosition = (c + 1)*Space + c*Child_Height;

				/*
				*	Update children position
				*/
				(*it)->Update();
				c++;
			}
		}
	}
}
