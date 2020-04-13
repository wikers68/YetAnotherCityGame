#include "stdafx.h"
#include "Camera.h"


CCamera::CCamera()
{
	Position = glm::vec3(5, 5, 5);
}


CCamera::~CCamera()
{
}

glm::mat4 CCamera::getMatriceView()
{
	return 	glm::lookAt(Position,
		glm::vec3(0.0),
		glm::vec3(0.0, 1.0, 0.0));
}
