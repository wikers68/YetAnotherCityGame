#pragma once
#include "../Context.h"
#include "../GUI/Gui2DRect.h"

class CMainMenu : 	public CContext
{
public:
	CMainMenu();
	~CMainMenu();

	CGui2DRect *_MenuBackGround;
	CGui2DRect *_ButtonGame;
	CGui2DRect *_ButtonInsideButtonGame;

	bool CreateContext() override;
	void RunContextLogic(float delta_t = 0.0f) override;

	// Inherited via CContext
	virtual void EventProcessing(SDL_Event evt) override;

	//callback function...
	void ButtonGameOnClick(CGui2DRect *caller);
	void IsOverButton(CGui2DRect *caller);
	void IsLeavingButton(CGui2DRect * caller);

};

