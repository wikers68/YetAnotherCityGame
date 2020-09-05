#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <list>

#include "../Shaders/ShaderManager.h"
//#include "Modeling\TerrainCurve.h"

class CTerrainCurve;

class CTerrainCells
{
public:
	CTerrainCells(CTerrainCells *parent);
	~CTerrainCells();

	CTerrainCells *parentCell;

	unsigned int level;

	const int maxLevel = 2;

	GLuint heightMapTExture;

	CTerrainCells *childNorthWest;
	CTerrainCells *childNorthEast;
	CTerrainCells *childSouthEast;
	CTerrainCells *childSoutWest;

	void SetSquareSize(float size);

	void Draw(unsigned int NumberOfVertex);

	void UpdateHeightMap(std::list<CTerrainCurve*> *SetOfTerrainCurve);

	/*
	*	Create the render texture for heightmap
	*/
	void InitHeightMap(void);

	static int getTerrainResolution(void) { return 40; }

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
	float LongitudePosition;
	float LatitudePosition;

};

