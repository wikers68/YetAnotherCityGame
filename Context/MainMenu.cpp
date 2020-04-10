#include "stdafx.h"
#include "MainMenu.h"

#include "../GUI/GuiBaseRect.h"
#include "../GUI/Gui2DRect.h"
#include "../GUI/GuiTextureRect.h"

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

	_ButtonTexture = new CGuiTextureRect(200, 100, 0, 0);
	CTexture *_textureButton = new CTexture();
	_textureButton->LoadFromFile("../GameRessources/media/GUI/textures/test.png");
	_ButtonTexture->SetTexture(_textureButton);
	RegisterGui_ForEvent_Handling(_ButtonTexture);
	_ButtonTexture->Evenment->Set_IsOver_Callback(std::bind(&CMainMenu::TextureIsOver, this, std::placeholders::_1));
	_ButtonTexture->Evenment->Set_IsLeaving_Callback(std::bind(&CMainMenu::TextureIsLeaving, this, std::placeholders::_1));
	_MenuBackGround->AddChild(_ButtonTexture);

	_buttonExitGame = new CGui2DRect(100, 50, 500, 500);
	_buttonExitGame->Evenment->Set_OnClick_Callback(std::bind(&CMainMenu::ExitGame, this, std::placeholders::_1));
	_buttonExitGame->Evenment->Set_IsOver_Callback(std::bind(&CMainMenu::IsOverButton, this, std::placeholders::_1));
	_buttonExitGame->Evenment->Set_IsLeaving_Callback(std::bind(&CMainMenu::IsLeavingButton, this, std::placeholders::_1));
	_buttonExitGame->SetBackGroundColor(0.0f, 0.3f, 1.0f);
	_MenuBackGround->AddChild(_buttonExitGame);
	RegisterGui_ForEvent_Handling(_buttonExitGame);

	hello = new CDisplayText(0,0,200,0);
	hello->SetText(L"Ca marche! => €");
	_MenuBackGround->AddChild(hello);

	quit = new CDisplayText(0,0,0,0);
	quit->SetText(L"EeXxIt");
	_buttonExitGame->AddChild(quit);

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

void CMainMenu::ExitGame(CGui2DRect * caller)
{
	CContextManager::Instance().stopApplication();
}

void CMainMenu::TextureIsOver(CGuiTextureRect * caller)
{
	caller->ModulateColor(0.5f, 0.5f, 0.5f);
}

void CMainMenu::TextureIsLeaving(CGuiTextureRect * caller)
{
	caller->ModulateColor(1.0f, 1.0f, 1.0f);
}
