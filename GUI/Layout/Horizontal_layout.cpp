#include "stdafx.h"
#include "Horizontal_layout.h"


CHorizontal_layout::CHorizontal_layout(std::string argWidth, std::string  argHeight, int argHorizontalPosition, int argVerticalPosition,int spaceBetweenChild) : CGuiBaseRect(argWidth, argHeight, argHorizontalPosition, argVerticalPosition)
{
	Space = spaceBetweenChild;
}


CHorizontal_layout::~CHorizontal_layout()
{
}

void CHorizontal_layout::AddChild(CGuiBaseRect * argChild)
{
	CGuiBaseRect::AddChild(argChild);
	Update();
}

void CHorizontal_layout::Update(void)
{
	if (_Child)
	{
		int NumberOfChild = _Child->size();

		if (NumberOfChild > 0)
		{
			int numberOfSpace = NumberOfChild + 1;

			int TotalSpaceWidth = numberOfSpace * Space;

			int RemainingWdith = this->getWidth() - TotalSpaceWidth;

			int Child_Width = RemainingWdith / NumberOfChild;

			std::list<CGuiBaseRect*>::iterator it;
			int c = 0;

			for (it = _Child->begin(); it != _Child->end(); it++)
			{
				(*it)->SetCommandString(std::to_string(Child_Width).append("p"),Translate_Size::WIDTH);
				(*it)->_HorizontalPosition = (c + 1)*Space + c*Child_Width;

				/*
				*	Update children position
				*/
				(*it)->Update();
				c++;
			}
		}
	}
}
