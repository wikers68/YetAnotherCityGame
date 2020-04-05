#pragma once

/*
*	Base class to manage game context such as main menu, in game logic, terrain editor, asset...
*/

#include <SDL.h> //for event handling

class CContext
{
public:
	CContext();
	~CContext();

	virtual bool CreateContext();
	bool ActivateContext();
	virtual bool RunContext(float delta_t = 0.0f);
	bool DestroyContext();

	//dispatch event inside the context
	void ManageEvent(void);

	virtual void EventProcessing(SDL_Event evt) = 0;
};

