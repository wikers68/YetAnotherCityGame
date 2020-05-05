#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <SDL.h>
#include <iostream>

#include "../Option.h"

class CCamera
{
public:
	CCamera();
	~CCamera();

	glm::vec3 Position;
	
	glm::mat4 getMatriceView();

	void LastMoussePosition(int Px, int Py);

	void Proceed_Event(SDL_Event evt, float delta_t = 0.0);

	glm::vec3 getViewDirection(void);

	bool isFreeToRotate;

private:
	int lastMousseXposition;
	int lastMousseYposition;

	float latitude;
	float longitude;
};

