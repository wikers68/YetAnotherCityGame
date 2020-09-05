#include "stdafx.h"
#include "TerrainCells.h"

/*
*	Placed here to avoid circular dependency while compiling
*/
#include "Modeling\TerrainCurve.h"

CTerrainCells::CTerrainCells(CTerrainCells *parent)
{
	parentCell = nullptr;
	level = 1;
	LongitudeSize = LatitudeSize = 0.0f;
	LongitudePosition = LatitudePosition = 0.0f;

	InitHeightMap();
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
	glm::vec4 SizePosition = glm::vec4(LongitudeSize, LatitudeSize, LongitudePosition, LatitudePosition);

	glUniform4fv(glGetUniformLocation(CShaderManager::getInstance().getShader("CTerrain_Shader")->getShaderProgram(), "SizePosition"),
		1, glm::value_ptr(SizePosition));

	glUniform1i(glGetUniformLocation(CShaderManager::getInstance().getShader("CTerrain_Shader")->getShaderProgram(), "heightMap"), 0);
	glBindTexture(GL_TEXTURE_2D, heightMapTExture);

	glDrawArrays(GL_TRIANGLES, 0, NumberOfVertex);
}

void CTerrainCells::UpdateHeightMap(std::list<CTerrainCurve*>* SetOfTerrainCurve)
{
	if (SetOfTerrainCurve->size() > 0)
	{
		/*
		*	Bind the heightmap texture to the height map framebuffer curently binded
		*/
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, heightMapTExture, 0);
		
		glViewport(0, 0, this->getTerrainResolution(), getTerrainResolution());
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		std::list<CTerrainCurve*>::iterator it;

		for (it = SetOfTerrainCurve->begin(); it != SetOfTerrainCurve->end(); it++)
		{
			glBindVertexArray((*it)->VertexArray_TriangleHeight);

			GLuint shader = CShaderManager::getInstance().getShader("CTerrainCells_Heightmap_Shaders")->getShaderProgram();
			glUseProgram(shader);

			glUniform2f(glGetUniformLocation(shader, "TerrainCell_Position"), this->LongitudePosition, this->LatitudePosition);

			glUniform2f(glGetUniformLocation(shader, "TerrainCell_Size"), this->LongitudeSize, this->LatitudeSize);

			glDrawArrays(GL_TRIANGLES, 0,(*it)->numberOfVertex_TerrainHeight);
		}

		glViewport(0, 0, 1280, 760);
	}
}

void CTerrainCells::InitHeightMap(void)
{
	glGenTextures(1, &heightMapTExture);
	glBindTexture(GL_TEXTURE_2D, heightMapTExture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_R16,
		CTerrainCells::getTerrainResolution(), CTerrainCells::getTerrainResolution(),
		0, GL_RED, GL_FLOAT, (void*)0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, 0);
}
