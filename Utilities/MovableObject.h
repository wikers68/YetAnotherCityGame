#pragma once

#include "../Camera/Camera.h"
#include "Axis.h"
#include "../Context/ContextManager.h"

class CAxis;

/*
*	Class to model object position in space
*/

class CMovableObject
{
public:
	CMovableObject();
	~CMovableObject();

	/*
	*	Horizontal position
	*/
	float X;
	float Y;

	/*
	*	Vertical position
	*/
	float Height;

	/*
	*	 Used to draw axis
	*/

	CAxis *Height_Axis;

	void DrawAxis(CCamera *activeCamera, float delta_t = 0.0f);
};

