#pragma once

/*
*	Base class to manage game context such as main menu, in game logic, terrain editor, asset...
*/

class CContext
{
public:
	CContext();
	~CContext();

	virtual bool CreateContext();
	bool ActivateContext();
	virtual bool RunContext(float delta_t = 0.0f);
	bool DestroyContext();
};

