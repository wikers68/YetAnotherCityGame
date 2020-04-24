#include "stdafx.h"
#include "Horizontal_layout.h"


CHorizontal_layout::CHorizontal_layout(Widget_Style style,int spaceBetweenChild) : CGuiBaseRect(style)
{
	Space = spaceBetweenChild;
}


CHorizontal_layout::~CHorizontal_layout()
{
}

void CHorizontal_layout::AddChild(CGuiBaseRect * argChild)
{
	/*
	*	Create an empty widget with:
	*		- height = parent height,
	*		- width, calculated to take in account the number of child in the layout
	*/
	Widget_Style slotStyle;
	slotStyle.hPosition = 0;
	slotStyle.vPosition = style.vPosition;

	CEmptySlot *slot = new CEmptySlot(slotStyle);
	slot->AddChild(argChild);

	CGuiBaseRect::AddChild(slot);
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
				(*it)->style.hSize.AbsOrRel = ABS_REL::_ABSOLUTE;
				(*it)->style.hSize.size = Child_Width;
				(*it)->style.hPosition = (c + 1)*Space + c*Child_Width;

				/*
				*	 Set the parent height
				*/
				(*it)->style.vSize.AbsOrRel = ABS_REL::_RELATIVE;
				(*it)->style.vSize.size = 100;
				(*it)->style.vSize.relTo = SIZE_RELATIVE_TO::PARENT;

				/*
				*	Update children position
				*/
				(*it)->Update();
				c++;
			}
		}
	}
}
