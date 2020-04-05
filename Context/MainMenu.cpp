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
	_MenuBackGround = new CGui2DRect(1240, 700, 0, 0);
	_ButtonGame = new CGui2DRect(250, 100, 100, 400);
	_ButtonInsideButtonGame = new CGui2DRect(50, 50, 100, 25);
	
	_MenuBackGround->AddChild(_ButtonGame);
	_ButtonGame->AddChild(_ButtonInsideButtonGame);


	return false;
}

bool CMainMenu::RunContext(float delta_t)
{
	_MenuBackGround->Draw();
	//_ButtonGame->Draw(); //move in parent draw function
	return false;
}