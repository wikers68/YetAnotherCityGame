#include "stdafx.h"
#include "GameContext.h"


CGameContext::CGameContext()
{
	gameTErrain = new CTerrain();
	gameTErrain->InitGrid();
	gameTErrain->masterCells->SetSquareSize(5);
}


CGameContext::~CGameContext()
{
}

void CGameContext::RunContextLogic(float delta_t)
{
	C3DContext::RunContextLogic(delta_t);
}

void CGameContext::EventProcessing(SDL_Event evt, float delta_t)
{
	C3DContext::EventProcessing(evt, delta_t);
}
