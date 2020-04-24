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
	*	Common style on button
	*/

	Widget_Style wsBackground;
	wsBackground.hPosition = HORIZONTAL_CENTER;
	wsBackground.vPosition = VERTICAL_CENTER;
	wsBackground.hSize.AbsOrRel = ABS_REL::_ABSOLUTE;
	wsBackground.hSize.size = COption::getInstance().Get_Horizontal_Resolution();
	wsBackground.vSize.AbsOrRel = ABS_REL::_ABSOLUTE;
	wsBackground.vSize.size = COption::getInstance().Get_Vertical_Resolution();

	Widget_Style wsButton;
	wsButton.hPosition = HORIZONTAL_CENTER;
	wsButton.vPosition = VERTICAL_CENTER;
	wsButton.hSize.AbsOrRel = ABS_REL::_ABSOLUTE;
	wsButton.hSize.size = 400;
	wsButton.vSize.AbsOrRel = ABS_REL::_RELATIVE;
	wsButton.vSize.relTo = SIZE_RELATIVE_TO::PARENT;
	wsButton.vSize.size = 100;

	Widget_Style wsText;
	wsText.hPosition = HORIZONTAL_CENTER;
	wsText.vPosition = VERTICAL_CENTER;

	/*
	*	Set Background Texture
	*/
	_MenuBackGround = new CGuiTextureRect(wsBackground);
	_MenuBackGround->Update();
	CTexture *_textureButton = new CTexture();
	_textureButton->LoadFromFile("../GameRessources/media/GUI/textures/background_menu_1920x1080.png");
	_MenuBackGround->SetTexture(_textureButton);

	/*
	*	vertical layout
	*/
	Widget_Style wsVerticalLayout;
	wsVerticalLayout.hPosition = 0;
	wsVerticalLayout.vPosition = VERTICAL_CENTER;
	wsVerticalLayout.hSize.AbsOrRel = ABS_REL::_RELATIVE;
	wsVerticalLayout.hSize.relTo = SIZE_RELATIVE_TO::PARENT;
	wsVerticalLayout.hSize.size = 100; // % 
	wsVerticalLayout.vSize.AbsOrRel = ABS_REL::_RELATIVE;
	wsVerticalLayout.vSize.relTo = SIZE_RELATIVE_TO::PARENT;
	wsVerticalLayout.vSize.size = 100; // 

	verticalLayout = new CVertical_layout(wsVerticalLayout,50);

	_MenuBackGround->AddChild(verticalLayout);

	/*
	*	Initialisation for play
	*/
	_ButtonStartNewGame = new CGui2DRect(wsButton);
	_ButtonStartNewGame->SetBackGroundColor(BUTTON_BACKGROUND_OVER_COLOR);
	verticalLayout->AddChild(_ButtonStartNewGame);
	_ButtonStartNewGame->Evenment->Set_OnClick_Callback(std::bind(&CMainMenu::ButtonStartNewGameOnClick, this, std::placeholders::_1));
	_ButtonStartNewGame->Evenment->Set_IsOver_Callback(std::bind(&CMainMenu::IsOverButton, this, std::placeholders::_1));
	_ButtonStartNewGame->Evenment->Set_IsLeaving_Callback(std::bind(&CMainMenu::IsLeavingButton, this, std::placeholders::_1));
	RegisterGui_ForEvent_Handling(_ButtonStartNewGame);
	
	PlayText = new CDisplayText(wsText);
	PlayText->SetText(L"Start New Game!");
	_ButtonStartNewGame->AddChild(PlayText);

	/*
	*	Initialisation for OpenGame
	*/
	_ButtonOpenGame = new CGui2DRect(wsButton);
	_ButtonOpenGame->SetBackGroundColor(BUTTON_BACKGROUND_OVER_COLOR);
	verticalLayout->AddChild(_ButtonOpenGame);
	_ButtonOpenGame->Evenment->Set_IsOver_Callback(std::bind(&CMainMenu::IsOverButton, this, std::placeholders::_1));
	_ButtonOpenGame->Evenment->Set_IsLeaving_Callback(std::bind(&CMainMenu::IsLeavingButton, this, std::placeholders::_1));
	RegisterGui_ForEvent_Handling(_ButtonOpenGame);

	OpenGameText = new CDisplayText(wsText);
	OpenGameText->SetText(L"Continue existing game!");
	_ButtonOpenGame->AddChild(OpenGameText);

	/*
	*	Initialisation for Editor
	*/
	_Editor = new CGui2DRect(wsButton);
	_Editor->SetBackGroundColor(BUTTON_BACKGROUND_OVER_COLOR);
	verticalLayout->AddChild(_Editor);
	_Editor->Evenment->Set_OnClick_Callback(std::bind(&CMainMenu::ButtonEditorOnClick, this, std::placeholders::_1));
	_Editor->Evenment->Set_IsOver_Callback(std::bind(&CMainMenu::IsOverButton, this, std::placeholders::_1));
	_Editor->Evenment->Set_IsLeaving_Callback(std::bind(&CMainMenu::IsLeavingButton, this, std::placeholders::_1));
	RegisterGui_ForEvent_Handling(_Editor);

	EditorText = new CDisplayText(wsText);
	EditorText->SetText(L"Editor");
	_Editor->AddChild(EditorText);

	/*
	*	Initialisation for Option
	*/
	_Option = new CGui2DRect(wsButton);
	_Option->SetBackGroundColor(BUTTON_BACKGROUND_OVER_COLOR);
	verticalLayout->AddChild(_Option);
	_Option->Evenment->Set_IsOver_Callback(std::bind(&CMainMenu::IsOverButton, this, std::placeholders::_1));
	_Option->Evenment->Set_IsLeaving_Callback(std::bind(&CMainMenu::IsLeavingButton, this, std::placeholders::_1));
	RegisterGui_ForEvent_Handling(_Option);

	OptionText = new CDisplayText(wsText);
	OptionText->SetText(L"Option");
	_Option->AddChild(OptionText);

	/*
	*	Initialization for exit button
	*/
	_buttonExitGame = new CGui2DRect(wsButton);
	_buttonExitGame->Evenment->Set_OnClick_Callback(std::bind(&CMainMenu::ExitGame, this, std::placeholders::_1));
	_buttonExitGame->Evenment->Set_IsOver_Callback(std::bind(&CMainMenu::IsOverButton, this, std::placeholders::_1));
	_buttonExitGame->Evenment->Set_IsLeaving_Callback(std::bind(&CMainMenu::IsLeavingButton, this, std::placeholders::_1));
	_buttonExitGame->SetBackGroundColor(BUTTON_BACKGROUND_OVER_COLOR);
	verticalLayout->AddChild(_buttonExitGame);
	RegisterGui_ForEvent_Handling(_buttonExitGame);

	quit = new CDisplayText(wsText);
	quit->SetText(L"Quit");
	_buttonExitGame->AddChild(quit);

	Widget_Style wsText_Version;
	wsText_Version.hPosition = HORIZONTAL_LEFT;
	wsText_Version.vPosition = VERTICAL_BOTTOM;
	wsText_Version.hSize.AbsOrRel = ABS_REL::_ABSOLUTE;
	wsText_Version.vSize.AbsOrRel = ABS_REL::_ABSOLUTE;
	wsText_Version.vSize.size = 50;

	Version = new CDisplayText(wsText_Version);
	Version->SetHeight(20);
	Version->SetText(L"YetAnotherCityGame V.?");
	_MenuBackGround->AddChild(Version);

	return false;
}

void CMainMenu::RunContextLogic(float delta_t)
{
	/*
	*	only draw the parent, child will be handled by parent
	*/
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
	caller->SetBackGroundColor(BUTTON_BACKGROUND_IsOVER_COLOR);
}

void CMainMenu::IsLeavingButton(CGui2DRect * caller)
{
	caller->SetBackGroundColor(BUTTON_BACKGROUND_OVER_COLOR);
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
	ChangeContext<CGameContext>(this);
}
void CMainMenu::ButtonEditorOnClick(CGui2DRect * caller)
{
	ChangeContext<CEditorLandScreen>(this);
}

