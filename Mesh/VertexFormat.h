#pragma once

#include "GL/glew.h"
#include <glm/glm.hpp>

/*
*	Simple Struct to hold float3 vector with vertex position
*/
struct XYZ_Vertex
{
	glm::vec3 position;

	static void Set_GL_ArrayAttrib(void)
	{
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
	}
};