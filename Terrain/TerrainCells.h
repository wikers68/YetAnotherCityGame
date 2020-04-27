#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../Shaders/ShaderManager.h"

class CTerrainCells
{
public:
	CTerrainCells(CTerrainCells *parent);
	~CTerrainCells();

	CTerrainCells *parentCell;

	unsigned int level;

	void SetSquareSize(float size);

	void Draw(unsigned int NumberOfVertex);

	const int maxLevel = 2;

	CTerrainCells *childNorthWest;
	CTerrainCells *childNorthEast;
	CTerrainCells *childSouthEast;
	CTerrainCells *childSoutWest;

protected:

	/*
	*	Size along Y axis
	*/
	float LongitudeSize;

	/*
	*	Size along X axis
	*/
	float LatitudeSize;

	/*
	*	Define the center of the cell
	*/
	float HorizonPosition;
	float LatitudePosition;
};

