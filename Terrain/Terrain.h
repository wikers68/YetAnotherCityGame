#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <list>

#include "../Shaders/ShaderManager.h"
#include "../Camera/Camera.h"
#include "TerrainCells.h"
//#include "Modeling\TerrainCurve.h"

class CTerrainCurve;
class CTerrainCells;

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

	void CTerrain::InitGrid();

	void Draw(CCamera *activeCamera);

	CTerrainCells *masterCells;

	bool HasBeenInitialized;

	/*
	/	Frambuffer to be used to render height map 
	*/
	GLuint RenderHeightMapFrameBuffer;
	GLuint RenderDepth;

	/*
	*	return the max terrain height allowed the game
	*/
	static float MaxTerrainHeight(void) { return 1.0; }

	void UpdateHeightMap(std::list<CTerrainCurve*> *SetOfTerrainCurve);

private:
	void SetUp_RenderBuffer(void);
};

