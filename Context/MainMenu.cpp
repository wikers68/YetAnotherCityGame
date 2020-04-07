#include "stdafx.h"
#include "MainMenu.h"

#include "../GUI/GuiBaseRect.h"
#include "../GUI/Gui2DRect.h"

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
	_ButtonGame->SetBackGroundColor(0.0f, 0.0f, 1.0f);
	RegisterGui_ForEvent_Handling(_ButtonGame);
	_ButtonGame->Evenment->Set_OnClick_Callback(std::bind(&CMainMenu::ButtonGameOnClick,this,std::placeholders::_1));

	_ButtonInsideButtonGame = new CGui2DRect(50, 50, 100, 25);
	RegisterGui_ForEvent_Handling(_ButtonInsideButtonGame);
	_ButtonInsideButtonGame->Evenment->Set_IsOver_Callback(std::bind(&CMainMenu::IsOverButton, this, std::placeholders::_1));
	_ButtonInsideButtonGame->Evenment->Set_IsLeaving_Callback(std::bind(&CMainMenu::IsLeavingButton, this, std::placeholders::_1));
	
	_MenuBackGround->AddChild(_ButtonGame);
	_ButtonGame->AddChild(_ButtonInsideButtonGame);

	return false;
}

void CMainMenu::RunContextLogic(float delta_t)
{
	_MenuBackGround->Draw();

}

void CMainMenu::EventProcessing(SDL_Event evt)
{
}

void CMainMenu::ButtonGameOnClick(CGui2DRect *caller)
{
	caller->SetBackGroundColor(0.0f, 1.0f, 0.0f);
}

void CMainMenu::IsOverButton(CGui2DRect * caller)
{
	caller->SetBackGroundColor(0.0f, 1.0f, 1.0f);
}

void CMainMenu::IsLeavingButton(CGui2DRect * caller)
{
	caller->SetBackGroundColor(0.0f, 0.3f, 1.0f);
}