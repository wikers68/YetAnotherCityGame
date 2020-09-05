#include "stdafx.h"
#include "TerrainCurve.h"


CTerrainCurve::CTerrainCurve(CTerrainEditor *ContextExecution) : CEventTarget()
{
	this->ContextExecution = ContextExecution;

	LastID_ControlPoint = -1;

	/*NumberOfVertex = 0;*/

	ToBeUpdated = true;

	SetOfControlPoint = new std::map<int, CControlPoint*>();

	glGenVertexArrays(1, &VertexArray_Curve);
	glBindVertexArray(VertexArray_Curve);

	/*
	*	Create an empty buffer, will be fill later
	*/
	glGenBuffers(1, &VertexBuffer_Curve);
	glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer_Curve);
	glBufferData(GL_ARRAY_BUFFER, 0, (void*)0, GL_DYNAMIC_DRAW);
	XYZ_Vertex::Set_GL_ArrayAttrib();

	
	glGenVertexArrays(1, &VertexArray_TriangleHeight);
	glBindVertexArray(VertexArray_TriangleHeight);

	glGenBuffers(1, &VertexBuffer_TriangleHeight);
	glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer_TriangleHeight);
	glBufferData(GL_ARRAY_BUFFER, 0, (void*)0, GL_DYNAMIC_DRAW);
	XYZ_Vertex::Set_GL_ArrayAttrib();

	isSelected = false;

	numberOfVertex_TerrainHeight = 0;
}


CTerrainCurve::~CTerrainCurve()
{
}

void CTerrainCurve::AddControlPoint(CControlPoint * arg)
{
	LastID_ControlPoint++;

	SetOfControlPoint->insert(std::pair<int, CControlPoint*>(LastID_ControlPoint, arg));

	ToBeUpdated = true;
}

void CTerrainCurve::Draw(CCamera *activeCamera)
{
	/*
	*	First, draw the line, then children point
	*/

	//if (ToBeUpdated)
	//{
		RebuildVertexBuffer();
	//}

	DrawHeightTriangle(activeCamera);

	glBindVertexArray(VertexArray_Curve);

	GLuint shaderProg = CShaderManager::getInstance().getShader("CTerrainCurve_Shader")->getShaderProgram();
	glUseProgram(shaderProg);

	glm::mat4 model = glm::mat4(1.0f);
	
	glUniformMatrix4fv(glGetUniformLocation(shaderProg, "Model"), 1, GL_FALSE, glm::value_ptr(model));

	glUniformMatrix4fv(glGetUniformLocation(shaderProg, "View"),
		1, GL_FALSE,
		glm::value_ptr(activeCamera->getMatriceView())
	);

	glUniformMatrix4fv(glGetUniformLocation(shaderProg, "Projection"),
		1, GL_FALSE,
		glm::value_ptr(COption::getInstance().getMatriceProjection())
	);

	glUniform1i(glGetUniformLocation(shaderProg, "ID"), this->getId());

	float maxheight = CTerrain::MaxTerrainHeight();
	glUniform1f(glGetUniformLocation(shaderProg, "maxHeight"), maxheight );

	if (isSelected)
	{
		glUniform3f(glGetUniformLocation(shaderProg, "Color"), 0.0, 1.0, 0.3);
	}
	else
	{
		glUniform3f(glGetUniformLocation(shaderProg, "Color"), 0.0, 0.3, 1.0);
	}

	if (SetOfControlPoint->size() > 1)
	{
		glDrawArrays(GL_LINE_STRIP, 0, SetOfControlPoint->size());
	}

	/*
	*	Draw children point
	*/
	if (isSelected)
	{
		std::map<int, CControlPoint*>::iterator it;

		for (it = SetOfControlPoint->begin(); it != SetOfControlPoint->end(); it++)
		{
			it->second->Draw(activeCamera);
		}
	}

}

void CTerrainCurve::RebuildVertexBuffer(void)
{
	int numberOfControlPoint = this->SetOfControlPoint->size();

	CCurvePoint *cp = (CCurvePoint*)calloc(numberOfControlPoint, sizeof(CCurvePoint));

	std::map<int, CControlPoint*>::iterator it;
	
	int Indice = 0;

	for (it = SetOfControlPoint->begin(); it != SetOfControlPoint->end(); it++)
	{
		CCurvePoint CurvePoint;
		CurvePoint.position = glm::vec3(it->second->X, it->second->Y, it->second->Height);

		cp[Indice] = CurvePoint;

		Indice++;

		std::cout << it->second->Height << std::endl;
	}
	glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer_Curve);
	glBufferData(GL_ARRAY_BUFFER, numberOfControlPoint * sizeof(CCurvePoint), cp, GL_DYNAMIC_DRAW);
	//glBufferSubData(GL_ARRAY_BUFFER, (void*)0, numberOfControlPoint * sizeof(CCurvePoint), cp);

	/*
	*	Update the vertex bufer with triangle to set heighmap height
	*/
	GenerateHeightRendering();

	ToBeUpdated = false;

}

void CTerrainCurve::DeleteSelectedPoint(void)
{
	if (SetOfControlPoint->size() > 0)
	{
		std::map<int, CControlPoint*>::iterator it;

		for (it = SetOfControlPoint->begin(); it != SetOfControlPoint->end(); it++)
		{
			if (it->second->isSelected)
			{
				SetOfControlPoint->erase(it->first);
				it = SetOfControlPoint->begin();
				ToBeUpdated = true;
			}
		}
	}
}

void CTerrainCurve::GenerateHeightRendering(void)
{
	if (SetOfControlPoint->size() >= 2)
	{
		int numberOfSegment = SetOfControlPoint->size() - 1;

		/*
		*	Allocate array for rendering vertex:
		*		- 4 triangles by line segment,
		*		- 3 vertex per triangle
		*/
		numberOfVertex_TerrainHeight = numberOfSegment * 4 * 3;
		XYZ_Vertex *vt = (XYZ_Vertex*)calloc(numberOfVertex_TerrainHeight,sizeof(XYZ_Vertex));

		for (int indexSegment = 0; indexSegment < numberOfSegment; indexSegment++)
		{
			CControlPoint StartSegmentPoint = *SetOfControlPoint->find(indexSegment)->second;
			CControlPoint EndSegmentPoint = *SetOfControlPoint->find(indexSegment+1)->second;

			glm::vec3 dir = glm::normalize(StartSegmentPoint.getVec3() - EndSegmentPoint.getVec3());
			glm::vec3 ortho = 0.25f*glm::vec3(dir.y, -dir.x, 0.0f);

			//TODO: define altitude pt.position.z = 0.0f; as a function of CControlePoint height profil

			XYZ_Vertex Start;
			Start.position = StartSegmentPoint.getVec3();

			XYZ_Vertex End;
			End.position = EndSegmentPoint.getVec3();
			
			XYZ_Vertex pt0;
			pt0.position = StartSegmentPoint.getVec3() + ortho;
			pt0.position.z = 0.0f;

			XYZ_Vertex pt1;
			pt1.position = EndSegmentPoint.getVec3() + ortho;
			pt1.position.z = 0.0f;

			XYZ_Vertex pt2;
			pt2.position = EndSegmentPoint.getVec3() - ortho;
			pt2.position.z = 0.0f; 

			XYZ_Vertex pt3;
			pt3.position = StartSegmentPoint.getVec3() - ortho;
			pt3.position.z = 0.0f; 

			/*
			*	We create two rectangle, one on each side of the curve
			*/

			vt[(12 * indexSegment)] = Start;
			vt[(12 * indexSegment) +1] = End;
			vt[(12 * indexSegment) + 2] = pt1;

			vt[(12 * indexSegment) +3] = Start;
			vt[(12 * indexSegment) + 4] = pt1;
			vt[(12 * indexSegment) + 5] = pt0;

			vt[(12 * indexSegment) + 6] = Start;
			vt[(12 * indexSegment) + 7] = End;
			vt[(12 * indexSegment) + 8] = pt2;

			vt[(12 * indexSegment) + 9] = Start;
			vt[(12 * indexSegment) + 10] = pt2;
			vt[(12 * indexSegment) + 11] = pt3;
		}

		glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer_TriangleHeight);
		glBufferData(GL_ARRAY_BUFFER, numberOfVertex_TerrainHeight * sizeof(XYZ_Vertex), vt, GL_DYNAMIC_DRAW);

		//delete vt;

		ContextExecution->Update_Heightmap();
	}
}

bool CTerrainCurve::CheckMouseClick(SDL_Event evt)
{
	isSelected = true;
	this->ContextExecution->SelectedCurve = this;

	return false;
}

void CTerrainCurve::CheckMouseIsOver(SDL_Event evt)
{
}

void CTerrainCurve::CheckMouseIsLeaving(SDL_Event evt)
{
}

void CTerrainCurve::DrawHeightTriangle(CCamera *activeCamera)
{

	glBindVertexArray(VertexArray_TriangleHeight);

	GLuint shaderProg = CShaderManager::getInstance().getShader("CTerrainCells_Heightmap_3D")->getShaderProgram();
	glUseProgram(shaderProg);

	glm::mat4 model = glm::mat4(1.0f);

	glUniformMatrix4fv(glGetUniformLocation(shaderProg, "Model"), 1, GL_FALSE, glm::value_ptr(model));

	glUniformMatrix4fv(glGetUniformLocation(shaderProg, "View"),
		1, GL_FALSE,
		glm::value_ptr(activeCamera->getMatriceView())
	);

	glUniformMatrix4fv(glGetUniformLocation(shaderProg, "Projection"),
		1, GL_FALSE,
		glm::value_ptr(COption::getInstance().getMatriceProjection())
	);

	//glUniform1i(glGetUniformLocation(shaderProg, "ID"), this->getId());

	//float maxheight = CTerrain::MaxTerrainHeight();
	//glUniform1f(glGetUniformLocation(shaderProg, "maxHeight"), maxheight);

	/*if (isSelected)
	{
		glUniform3f(glGetUniformLocation(shaderProg, "Color"), 0.0, 1.0, 0.3);
	}
	else
	{
		glUniform3f(glGetUniformLocation(shaderProg, "Color"), 0.0, 0.3, 1.0);
	}*/

	if (numberOfVertex_TerrainHeight > 2)
	{
		glDrawArrays(GL_TRIANGLES, 0, numberOfVertex_TerrainHeight);
	}
}
