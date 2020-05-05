#pragma once

#include <SDL.h> //for event handling

class CEventTarget
{
public:
	CEventTarget();
	~CEventTarget();

	void setId(int arg);
	int getId(void);

	virtual bool CheckMouseClick(SDL_Event evt) = 0;
	virtual void CheckMouseIsOver(SDL_Event evt) = 0;
	virtual void CheckMouseIsLeaving(SDL_Event evt) = 0;

	virtual void Mouse_Button_Up(SDL_Event evt) {};

private:
	int Id;
};

