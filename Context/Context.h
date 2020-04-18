#pragma once

/*
*	Base class to manage game context such as main menu, in game logic, terrain editor, asset...
*/

#include <SDL.h> //for event handling
#include <list>

#include "../GUI/GuiBaseRect.h"
#include "../GUI/Gui2DRect.h"
#include "ContextManager.h"

class CContext
{
public:
	CContext();
	~CContext();

	std::list<CGuiBaseRect*> *_GuiElements;

	virtual bool CreateContext();
	bool ActivateContext();
	virtual void RunContextLogic(float delta_t = 0.0f) = 0;
	bool RunContext(float delta_t = 0.0f);
	bool DestroyContext();

	//dispatch event inside the context
	void ManageEvent(float delta_t = 0.0f);

	virtual void EventProcessing(SDL_Event evt, float delta_t = 0.0f) = 0;

	void RegisterGui_ForEvent_Handling(CGuiBaseRect *arg);

	template<class C>
	void ChangeContext(CContext *currentContext)
	{
		C *nContext = new C();

		if (static_cast<CContext*>(nContext))
		{
			nContext->CreateContext();
			nContext->ActivateContext();

			//~currentContext(); //does it works ? Not sure
		}
	}

};
