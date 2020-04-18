#include "stdafx.h"
#include "GameContext.h"


CGameContext::CGameContext()
{

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
