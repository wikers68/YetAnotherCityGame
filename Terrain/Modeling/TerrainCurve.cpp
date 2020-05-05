#include "stdafx.h"
#include "TerrainCurve.h"


CTerrainCurve::CTerrainCurve(CTerrainEditor *ContextExecution) : CEventTarget()
{
	this->ContextExecution = ContextExecution;

	LastID_ControlPoint = 0;

	/*NumberOfVertex = 0;*/

	ToBeUpdated = true;

	SetOfControlPoint = new std::map<int, CControlPoint*>();

	glGenVertexArrays(1, &VertexArray);
	glBindVertexArray(VertexArray);

	/*
	*	Create an empty buffer, will be fill later
	*/
	glGenBuffers(1, &VertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, 0, (void*)0, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	isSelected = false;

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

	if (ToBeUpdated)
	{
		RebuildVertexBuffer();
	}

	glBindVertexArray(VertexArray);

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
	glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, numberOfControlPoint * sizeof(CCurvePoint), cp, GL_DYNAMIC_DRAW);
	//glBufferSubData(GL_ARRAY_BUFFER, (void*)0, numberOfControlPoint * sizeof(CCurvePoint), cp);

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
