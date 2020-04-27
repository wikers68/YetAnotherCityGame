#include "stdafx.h"
#include "Vertical_layout.h"


CVertical_layout::CVertical_layout(Widget_Style style, int spaceBetweenChild) : CGuiBaseRect(style)
{
	Space = spaceBetweenChild;
}


CVertical_layout::~CVertical_layout()
{
}

void CVertical_layout::AddChild(CGuiBaseRect * argChild)
{
	/*
	*	We create an empty slot. Then we add the child
	*/
	Widget_Style slotStyle;
	slotStyle.hPosition = style.hPosition;
	slotStyle.vPosition = 0;

	CEmptySlot *slot = new CEmptySlot(slotStyle);
	slot->AddChild(argChild);

	CGuiBaseRect::AddChild(slot);
	Update();
}

void CVertical_layout::Update(void)
{
	CGuiBaseRect::Update();

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
				(*it)->style.hSize.AbsOrRel = ABS_REL::_RELATIVE;  //ABS_REL::_RELATIVE;
				(*it)->style.hSize.relTo = SIZE_RELATIVE_TO::PARENT;
				(*it)->style.hSize.size = 100.0;

				(*it)->style.vSize.AbsOrRel = ABS_REL::_ABSOLUTE;
				(*it)->style.vSize.size = Child_Height;//SetCommandString(std::to_string(Child_Height).append("p"),Translate_Size::HEIGHT);
				(*it)->style.vPosition = (c + 1)*Space + c*Child_Height;

				/*
				*	Update children position
				*/
				(*it)->Update();
				c++;
			}
		}
	}
}
