#include "stdafx.h"
#include "Terrain.h"

/*
*	Placed here to avoid circular dependency while compiling
*/
#include "Modeling\TerrainCurve.h"


CTerrain::CTerrain()
{
	masterCells = new CTerrainCells(nullptr);
	HasBeenInitialized = false;

	SetUp_RenderBuffer();
}


CTerrain::~CTerrain()
{
}

void CTerrain::InitGrid()
{
	GLuint VertexBuffer;
	GLuint VertexArrayAtt;

	glGenVertexArrays(1, &TerrainVertexArray);
	glGenBuffers(1, &VertexBuffer);


	int NombreCarre = CTerrainCells::getTerrainResolution() - 1;

	ArraySize = 3 * NombreCarre * NombreCarre * 2; //2 triangles à 3 vertices par carré
	float *EmplacementMemoireVertex = (float*)calloc(3 * ArraySize, sizeof(float));

	float PasSubdivision = 1.0f / (float)NombreCarre;

	int Position_Memoire = 0;

	for (int Sub_X = 0; Sub_X < NombreCarre; Sub_X++)
	{
		float xMin = Sub_X*PasSubdivision;
		float xMax = (Sub_X + 1)*PasSubdivision;

		for (int Sub_Y = 0; Sub_Y < NombreCarre; Sub_Y++)
		{
			float yMin = Sub_Y*PasSubdivision;
			float yMax = (Sub_Y + 1)*PasSubdivision;


			EmplacementMemoireVertex[Position_Memoire] = xMax;
			Position_Memoire++;
			EmplacementMemoireVertex[Position_Memoire] = yMin;
			Position_Memoire++;
			EmplacementMemoireVertex[Position_Memoire] = 0.0;
			Position_Memoire++;

			EmplacementMemoireVertex[Position_Memoire] = xMin;
			Position_Memoire++;
			EmplacementMemoireVertex[Position_Memoire] = yMax;
			Position_Memoire++;
			EmplacementMemoireVertex[Position_Memoire] = 0.0;
			Position_Memoire++;

			EmplacementMemoireVertex[Position_Memoire] = xMin;
			Position_Memoire++;
			EmplacementMemoireVertex[Position_Memoire] = yMin;
			Position_Memoire++;
			EmplacementMemoireVertex[Position_Memoire] = 0.0;
			Position_Memoire++;

			//triangle 2
			EmplacementMemoireVertex[Position_Memoire] = xMax;
			Position_Memoire++;
			EmplacementMemoireVertex[Position_Memoire] = yMin;
			Position_Memoire++;
			EmplacementMemoireVertex[Position_Memoire] = 0.0;
			Position_Memoire++;

			EmplacementMemoireVertex[Position_Memoire] = xMax;
			Position_Memoire++;
			EmplacementMemoireVertex[Position_Memoire] = yMax;
			Position_Memoire++;
			EmplacementMemoireVertex[Position_Memoire] = 0.0;
			Position_Memoire++;

			EmplacementMemoireVertex[Position_Memoire] = xMin;
			Position_Memoire++;
			EmplacementMemoireVertex[Position_Memoire] = yMax;
			Position_Memoire++;
			EmplacementMemoireVertex[Position_Memoire] = 0.0;
			Position_Memoire++;
		}
	}

	glBindVertexArray(TerrainVertexArray);
	glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);

	int tailleBuffer = 3 * ArraySize * 4;
	glBufferData(GL_ARRAY_BUFFER, tailleBuffer, EmplacementMemoireVertex, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	HasBeenInitialized = true;
}

void CTerrain::Draw(CCamera *activeCamera)
{
	if (HasBeenInitialized)
	{
		GLuint terrainShader = CShaderManager::getInstance().getShader("CTerrain_Shader")->getShaderProgram();

		glUseProgram(terrainShader);
		glBindVertexArray(TerrainVertexArray);

		/*
		*	View Data from current active camera
		*/
		glUniformMatrix4fv(glGetUniformLocation(terrainShader, "View"),
			1, GL_FALSE,
			glm::value_ptr(activeCamera->getMatriceView())
		);

		glUniformMatrix4fv(glGetUniformLocation(terrainShader, "Projection"),
			1, GL_FALSE,
			glm::value_ptr(COption::getInstance().getMatriceProjection())
		);

		glm::mat4 model = glm::mat4(1.0f);
		glUniformMatrix4fv(glGetUniformLocation(terrainShader, "Model"), 1, GL_FALSE, glm::value_ptr(model));

		if (masterCells)
		{
			masterCells->Draw(ArraySize);
		}
	}

}

void CTerrain::UpdateHeightMap(std::list<CTerrainCurve*>* SetOfTerrainCurve)
{
	/*
	*	Get the current Framebuffer ID (PBR rendering pass)
	*/
	GLint currentPBR_FrameBuffer;
	glGetIntegerv(GL_FRAMEBUFFER_BINDING, &currentPBR_FrameBuffer);
	
	/*
	*	Bind the framebuffer dedicated to heightmap rendering
	*/
	glBindFramebuffer(GL_FRAMEBUFFER, RenderHeightMapFrameBuffer);
	glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, RenderDepth);

	if (masterCells)
	{
		masterCells->UpdateHeightMap(SetOfTerrainCurve);
	}

	/*
	*	Restore the PBR Framebuffer
	*/
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, currentPBR_FrameBuffer);
}

void CTerrain::SetUp_RenderBuffer(void)
{
	/*
	*	Get the current Framebuffer ID (PBR rendering pass)
	*/
	GLint currentPBR_FrameBuffer;
	glGetIntegerv(GL_FRAMEBUFFER_BINDING, &currentPBR_FrameBuffer);

	glGenFramebuffers(1, &RenderHeightMapFrameBuffer);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, RenderHeightMapFrameBuffer);

	/*
	*		Set up depth buffer
	*/
	glGenRenderbuffers(1, &RenderDepth);
	glBindRenderbuffer(GL_RENDERBUFFER, RenderDepth);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24,
		CTerrainCells::getTerrainResolution(),
		CTerrainCells::getTerrainResolution());

	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, currentPBR_FrameBuffer);
}
