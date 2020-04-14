#pragma once
#include "./Context.h"
#include "./ContextManager.h"
#include "../GUI/Gui2DRect.h"
#include "../GUI/GuiTextureRect.h"
#include "../graphics/texture/Texture.h"
#include "../GUI/Font/DisplayText.h"
#include "./Game/GameContext.h"

#define BUTTON_WIDTH 300
#define BUTTON_HEIGHT 100
#define BUTTON_COLOR 0.13, 0.33, 0.50,1.0
#define BUTTON_COLOR_ISOVER 0.11f, 0.27f, 0.41f

class CMainMenu : 	public CContext
{
public:
	CMainMenu();
	~CMainMenu();

	CGuiTextureRect *_MenuBackGround;
	CGuiTextureRect *_ButtonTexture;

	CGui2DRect *_ButtonStartNewGame;
	CDisplayText *PlayText;

	CGui2DRect *_ButtonOpenGame;
	CDisplayText *OpenGameText;

	CGui2DRect *_Editor;
	CDisplayText *EditorText;

	CGui2DRect *_Option;
	CDisplayText *OptionText;

	CGui2DRect *_buttonExitGame;
	CDisplayText *quit;

	CDisplayText *Version;

	bool CreateContext() override;
	void RunContextLogic(float delta_t = 0.0f) override;

	// Inherited via CContext
	virtual void EventProcessing(SDL_Event evt, float delta_t = 0.0) override;

	//callback function...
	void ButtonGameOnClick(CGui2DRect *caller);
	void IsOverButton(CGui2DRect *caller);
	void IsLeavingButton(CGui2DRect * caller);
	void ExitGame(CGui2DRect *caller);

	void TextureIsOver(CGuiTextureRect *caller);
	void TextureIsLeaving(CGuiTextureRect *caller);

	void ButtonStartNewGameOnClick(CGui2DRect *caller);
};

