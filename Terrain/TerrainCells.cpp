#include "stdafx.h"
#include "TerrainCells.h"


CTerrainCells::CTerrainCells(CTerrainCells *parent)
{
	parentCell = nullptr;
	level = 1;
	LongitudeSize = LatitudeSize = 0.0f;
	HorizonPosition = LatitudePosition = 0.0f;
}


CTerrainCells::~CTerrainCells()
{
}

void CTerrainCells::SetSquareSize(float size)
{
	LongitudeSize = LatitudeSize = size;
}

void CTerrainCells::Draw(unsigned int NumberOfVertex)
{
	glm::vec4 SizePosition = glm::vec4(LongitudeSize, LatitudeSize, HorizonPosition, LatitudePosition);

	glUniform4fv(glGetUniformLocation(CShaderManager::getInstance().getShader("CTerrain_Shader")->getShaderProgram(), "SizePosition"),
		1, glm::value_ptr(SizePosition));

	glDrawArrays(GL_TRIANGLES, 0, NumberOfVertex);
}
