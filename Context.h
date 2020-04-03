#pragma once

/*
*	Base class to manage game context such as main menu, in game logic, terrain editor, asset...
*/

class CContext
{
public:
	CContext();
	~CContext();

	bool CreateContext();
	bool ActivateContext();
	bool RunContext();
	bool DestroyContext();
};

