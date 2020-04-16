#include "stdafx.h"
#include "Camera.h"


CCamera::CCamera()
{
	Position = glm::vec3(5, 5, 5);
	lastMousseXposition = lastMousseYposition = 0;

	latitude = - 45.0;
	longitude = 225.0;
}


CCamera::~CCamera()
{
}

glm::mat4 CCamera::getMatriceView()
{
	return 	glm::lookAt(Position,
		Position + getViewDirection(),
		glm::vec3(0.0, 0.0, 1.0));
}

void CCamera::Proceed_Event(SDL_Event evt, float delta_t)
{	
	/*
	*	When keyboard is pressed, it seems that mousse motion values are out or on border of the window. 
	*	To avoid no smooth motion, we check that mousse is in window and not on borders.
	*/
	if (evt.motion.y < COption::getInstance().Get_Vertical_Resolution()
		&& evt.motion.y > 0 
		&& evt.motion.x > 0
		&& evt.motion.x < COption::getInstance().Get_Horizontal_Resolution())
	{
		int newXposition = evt.motion.x;
		int newYposition = evt.motion.y;

		if (SDL_GetMouseState(nullptr, nullptr))
		{
			int deltaX_deplacement = lastMousseXposition - newXposition;
			int deltaY_deplacement = lastMousseYposition - newYposition;

			float scaledX_deplaceement = (float)deltaX_deplacement  * delta_t * COption::getInstance().getCamera_RotationSpeed();
			float scaledY_deplaceement = (float)deltaY_deplacement  * delta_t * COption::getInstance().getCamera_RotationSpeed();

			latitude += scaledY_deplaceement;
			longitude += scaledX_deplaceement;

			std::cout << evt.motion.x << " " << evt.motion.y << std::endl;
		}

		lastMousseXposition = newXposition;
		lastMousseYposition = newYposition;
	}
	
	switch (evt.type)
	{
		default: break;
		case SDL_MOUSEWHEEL:
			/*
			*	Zoom in if y > 0 & zoom out if y < 0
			*/
			Position += 5.0f*(float)evt.wheel.y * getViewDirection()*delta_t* COption::getInstance().getCamera_TranslationSpeed();
			break;
	}

	/*
	*	Keyboard Event (in qwerty ?)
	*/
	const Uint8 *state = SDL_GetKeyboardState(nullptr);

	if (state[SDL_SCANCODE_W])
	{
		Position += getViewDirection()*delta_t* COption::getInstance().getCamera_TranslationSpeed();
		//std::cout << Position.x << std::endl;
	}

	if (state[SDL_SCANCODE_S])
	{
		Position -= getViewDirection()*delta_t*COption::getInstance().getCamera_TranslationSpeed();
	}

}

glm::vec3 CCamera::getViewDirection(void)
{
	float projectedVector = cos(glm::radians(latitude));
	float Z = sin(glm::radians(latitude));

	float X = cos(glm::radians(longitude)) * projectedVector;
	float Y = sin(glm::radians(longitude)) * projectedVector;

	return glm::vec3(X, Y, Z);
}
