#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class CCamera
{
public:
	CCamera();
	~CCamera();

	glm::vec3 Position;
	
	glm::mat4 getMatriceView();
};

