#pragma once

#include "../Context.h"
#include "../../GUI/Gui2DRect.h"
#include "../../GUI/GuiTextureRect.h"
#include "../../GUI/Font/DisplayText.h"
#include "../../GUI/Layout/Vertical_layout.h"
#include "../../GUI/Layout/Horizontal_layout.h"

class CEditorLandScreen : public CContext
{
public:
	CEditorLandScreen();
	~CEditorLandScreen();

	CGuiTextureRect *background;

	// Inherited via CContext
	virtual void RunContextLogic(float delta_t = 0.0f) override;
	virtual void EventProcessing(SDL_Event evt, float delta_t = 0.0f) override;
};

