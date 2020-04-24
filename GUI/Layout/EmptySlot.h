#pragma once

#include "../GuiBaseRect.h"

class CEmptySlot : public CGuiBaseRect
{
public:
	CEmptySlot(Widget_Style style);
	~CEmptySlot();

	// Inherited via CGuiBaseRect
	virtual void DrawLocal(float delta_t = 0.0f) override;
	virtual void CheckMouseClick(SDL_Event evt) override;
	virtual void CheckMouseIsOver(SDL_Event evt) override;
	virtual void CheckMouseIsLeaving(SDL_Event evt) override;
};