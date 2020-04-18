#pragma once

#include "Context.h"
#include "../../3DGameObject/StaticObject.h"
#include "../../Camera/Camera.h"

class C3DContext : public CContext
{
public:
	C3DContext();
	~C3DContext();

	// Inherited via CContext
	virtual void RunContextLogic(float delta_t = 0.0f) override;
	virtual void EventProcessing(SDL_Event evt, float delta_t = 0.0) override;

	CStaticObject *debugObject;

	CCamera *camera;
};

