#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../Shaders/ShaderManager.h"
#include "../Camera/Camera.h"
#include "TerrainCells.h"

class CTerrain
{
public:
	CTerrain();
	~CTerrain();

	GLuint TerrainVertexArray;
	
	/*
	*	Number of vertex to be drawn 
	*/
	unsigned int ArraySize;

	void CTerrain::InitGrid(int ResolutionPoint);

	void Draw(CCamera *activeCamera);

	CTerrainCells *masterCells;

	bool HasBeenInitialized;
};

