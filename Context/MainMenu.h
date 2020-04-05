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
	bool RunContext(float delta_t = 0.0f) override;
};

