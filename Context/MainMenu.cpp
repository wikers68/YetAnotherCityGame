#include "stdafx.h"
#include "MainMenu.h"


CMainMenu::CMainMenu()
{
}


CMainMenu::~CMainMenu()
{
}

bool CMainMenu::CreateContext()
{
	_MenuBackGround = new CGui2DRect(400, 200, 0, 0,nullptr);
	return false;
}

bool CMainMenu::RunContext(float delta_t)
{
	_MenuBackGround->Draw();
	return false;
}