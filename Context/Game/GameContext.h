#pragma once

#include "../3DContext.h"
#include "../../3DGameObject/StaticObject.h"
#include "../../Camera/Camera.h"

class CGameContext : public C3DContext
{
public:
	CGameContext();
	~CGameContext();

	// Inherited via C3DContext
	virtual void RunContextLogic(float delta_t = 0.0f) override;
	virtual void EventProcessing(SDL_Event evt, float delta_t = 0.0) override;

};

