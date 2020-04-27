#pragma once

#include <string>
#include "../CommonGUIheader.h"


class CBarButton : public CGuiBaseRect
{
public:
	CBarButton(int BarHeight);
	~CBarButton();

	CGui2DRect *TopMenuBackGround;

	/*
	*	Main layout to size and place button
	*/
	CHorizontal_layout *hl;

	// Inherited via CGuiBaseRect
	virtual void DrawLocal(float delta_t = 0.0f) override;
	virtual bool CheckMouseClick(SDL_Event evt) override;
	virtual void CheckMouseIsOver(SDL_Event evt) override;
	virtual void CheckMouseIsLeaving(SDL_Event evt) override;

	CGui2DRect *AddTextualButton(std::wstring buttonTExt);
};

