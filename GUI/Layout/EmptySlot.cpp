#include "stdafx.h"
#include "EmptySlot.h"

CEmptySlot::CEmptySlot(Widget_Style style):CGuiBaseRect(style)
{
}

CEmptySlot::~CEmptySlot()
{
}

void CEmptySlot::DrawLocal(float delta_t)
{
}

bool CEmptySlot::CheckMouseClick(SDL_Event evt)
{
	return false;
}

void CEmptySlot::CheckMouseIsOver(SDL_Event evt)
{
}

void CEmptySlot::CheckMouseIsLeaving(SDL_Event evt)
{
}
