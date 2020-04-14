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
	/*
	*	Set Background Texture
	*/
	_MenuBackGround = new CGuiTextureRect(COption::getInstance().Get_Horizontal_Resolution(), COption::getInstance().Get_Vertical_Resolution(), 0, 0);
	CTexture *_textureButton = new CTexture();
	_textureButton->LoadFromFile("../GameRessources/media/GUI/textures/background_menu_1920x1080.png");
	_MenuBackGround->SetTexture(_textureButton);

	/*
	*	Initialisation for play
	*/
	_ButtonStartNewGame = new CGui2DRect(BUTTON_WIDTH, BUTTON_HEIGHT, 0, 0);
	_ButtonStartNewGame->SetBackGroundColor(BUTTON_COLOR);
	_MenuBackGround->AddChild(_ButtonStartNewGame);
	_ButtonStartNewGame->Evenment->Set_OnClick_Callback(std::bind(&CMainMenu::ButtonStartNewGameOnClick, this, std::placeholders::_1));
	_ButtonStartNewGame->Evenment->Set_IsOver_Callback(std::bind(&CMainMenu::IsOverButton, this, std::placeholders::_1));
	_ButtonStartNewGame->Evenment->Set_IsLeaving_Callback(std::bind(&CMainMenu::IsLeavingButton, this, std::placeholders::_1));
	RegisterGui_ForEvent_Handling(_ButtonStartNewGame);
	
	PlayText = new CDisplayText(0, 0, 0, 0);
	PlayText->SetText(L"Start New Game!");
	_ButtonStartNewGame->AddChild(PlayText);

	/*
	*	Initialisation for OpenGame
	*/
	_ButtonOpenGame = new CGui2DRect(BUTTON_WIDTH, BUTTON_HEIGHT, HORIZONTAL_CENTER, 150);
	_ButtonOpenGame->SetBackGroundColor(BUTTON_COLOR);
	_MenuBackGround->AddChild(_ButtonOpenGame);
	_ButtonOpenGame->Evenment->Set_IsOver_Callback(std::bind(&CMainMenu::IsOverButton, this, std::placeholders::_1));
	_ButtonOpenGame->Evenment->Set_IsLeaving_Callback(std::bind(&CMainMenu::IsLeavingButton, this, std::placeholders::_1));
	RegisterGui_ForEvent_Handling(_ButtonOpenGame);

	OpenGameText = new CDisplayText(0, 0, 0, 0);
	OpenGameText->SetText(L"Continue existing game!");
	_ButtonOpenGame->AddChild(OpenGameText);

	/*
	*	Initialisation for Editor
	*/
	_Editor = new CGui2DRect(BUTTON_WIDTH, BUTTON_HEIGHT, HORIZONTAL_LEFT, 300);
	_Editor->SetBackGroundColor(BUTTON_COLOR);
	_MenuBackGround->AddChild(_Editor);
	_Editor->Evenment->Set_IsOver_Callback(std::bind(&CMainMenu::IsOverButton, this, std::placeholders::_1));
	_Editor->Evenment->Set_IsLeaving_Callback(std::bind(&CMainMenu::IsLeavingButton, this, std::placeholders::_1));
	RegisterGui_ForEvent_Handling(_Editor);

	EditorText = new CDisplayText(0, 0, 0, 0);
	EditorText->SetText(L"Editor");
	_Editor->AddChild(EditorText);

	/*
	*	Initialisation for Option
	*/
	_Option = new CGui2DRect(BUTTON_WIDTH, BUTTON_HEIGHT, HORIZONTAL_RIGHT, 450);
	_Option->SetBackGroundColor(BUTTON_COLOR);
	_MenuBackGround->AddChild(_Option);
	_Option->Evenment->Set_IsOver_Callback(std::bind(&CMainMenu::IsOverButton, this, std::placeholders::_1));
	_Option->Evenment->Set_IsLeaving_Callback(std::bind(&CMainMenu::IsLeavingButton, this, std::placeholders::_1));
	RegisterGui_ForEvent_Handling(_Option);

	OptionText = new CDisplayText(0, 0, 0, 0);
	OptionText->SetText(L"Option");
	_Option->AddChild(OptionText);

	/*
	*	Initialisation for exit button
	*/
	_buttonExitGame = new CGui2DRect(BUTTON_WIDTH, BUTTON_HEIGHT, HORIZONTAL_CENTER, 500);
	_buttonExitGame->Evenment->Set_OnClick_Callback(std::bind(&CMainMenu::ExitGame, this, std::placeholders::_1));
	_buttonExitGame->Evenment->Set_IsOver_Callback(std::bind(&CMainMenu::IsOverButton, this, std::placeholders::_1));
	_buttonExitGame->Evenment->Set_IsLeaving_Callback(std::bind(&CMainMenu::IsLeavingButton, this, std::placeholders::_1));
	_buttonExitGame->SetBackGroundColor(BUTTON_COLOR);
	_MenuBackGround->AddChild(_buttonExitGame);
	RegisterGui_ForEvent_Handling(_buttonExitGame);

	quit = new CDisplayText(0,0,0,0);
	quit->SetText(L"Quit");
	_buttonExitGame->AddChild(quit);

	Version = new CDisplayText(0, 0, 0, 600);
	Version->SetHeight(20);
	Version->SetText(L"YetAnotherCityGame V.?");
	_MenuBackGround->AddChild(Version);
	
	return false;
}

void CMainMenu::RunContextLogic(float delta_t)
{
	_MenuBackGround->Draw();

}

void CMainMenu::EventProcessing(SDL_Event evt, float delta_t)
{
}

void CMainMenu::ButtonGameOnClick(CGui2DRect *caller)
{
	caller->SetBackGroundColor(0.0f, 1.0f, 0.0f);
}

void CMainMenu::IsOverButton(CGui2DRect * caller)
{
	caller->SetBackGroundColor(BUTTON_COLOR_ISOVER);
}

void CMainMenu::IsLeavingButton(CGui2DRect * caller)
{
	caller->SetBackGroundColor(BUTTON_COLOR);
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

void CMainMenu::ButtonStartNewGameOnClick(CGui2DRect * caller)
{
	CGameContext *gc = new CGameContext();
	gc->CreateContext();
	gc->ActivateContext();
}
