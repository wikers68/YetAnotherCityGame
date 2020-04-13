#pragma once

#include "../Context.h"
#include "../../3DGameObject/StaticObject.h"
#include "../../Camera/Camera.h"

class CGameContext : public CContext
{
public:
	CGameContext();
	~CGameContext();

	// Inherited via CContext
	virtual void RunContextLogic(float delta_t = 0.0f) override;
	virtual void EventProcessing(SDL_Event evt) override;

	CStaticObject *debugObject;

	CCamera *camera;
};

