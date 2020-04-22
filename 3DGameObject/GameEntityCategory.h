#pragma once

#include <string>

enum GameEntity_Category
{
	UNDEFINED,
	HOUSE,
	BUILDING,
};


/*
*	Convert an enum to a wstring
*/
static std::wstring Convert_GameEntity_CategoryToWstring(GameEntity_Category arg)
{
	switch (arg)
	{
	default:
		return std::wstring(L"No GameEntity_Category");
	}
}