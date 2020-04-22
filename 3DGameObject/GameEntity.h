#pragma once

/*
*	Base class to define all game entity properties as cost, placeable or not...
*/

#include "GameEntityCategory.h"

class CGameEntity
{
public:
	CGameEntity();
	~CGameEntity();

	GameEntity_Category Category;

	void Show(void) { isVisible = true; }
	void Hide(void) { isVisible = false; }

private:

	/*	during render pass:
	*		True: draw object 
	*		False: don't draw 
	*/
	bool isVisible;
};

