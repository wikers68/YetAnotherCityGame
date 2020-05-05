#include "stdafx.h"
#include "ControlPoint.h"


CControlPoint::CControlPoint(CTerrainEditor *ContextExecution, CTerrainCurve *CurveOwner) : CEventTarget(), CMovableObject()
{
	this->ContextExecution = ContextExecution;
	ContextExecution->RegisterGui_ForEvent_Handling(this);

	ParentCurve = CurveOwner;

	//X = Y = height = 0.0f;

	isSelected = false;

	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);

	/*
	*	"Unit vertex" (1,1,1) will be multiplied in shader with current point position (X,Y,Height)
	*	to get the real position (X,Y,Height); Usefull when we move point during terrain editing.
	*/
	float *vecteurUnitaire = (float*)calloc(3, sizeof(float));

	vecteurUnitaire[0] = 1.0f;
	vecteurUnitaire[1] = 1.0f;
	vecteurUnitaire[2] = 1.0f;

	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(float), vecteurUnitaire, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}


CControlPoint::~CControlPoint()
{
}

void CControlPoint::Draw(CCamera *activeCamera)
{
	DrawAxis(activeCamera);

	GLuint shaderProg = CShaderManager::getInstance().getShader("CControlPoint_Shader")->getShaderProgram();

	glBindVertexArray(vertexArray);
	glUseProgram(shaderProg);

	glUniform3f(glGetUniformLocation(shaderProg, "WorldPosition"),X,Y,Height);

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

	/*
	*	Set a color to the point if it's selected or not
	*/
	if (isSelected)
	{
		glUniform3f(glGetUniformLocation(shaderProg, "Color"), 1.0, 0.0, 0.0);
	}
	else
	{
		glUniform3f(glGetUniformLocation(shaderProg, "Color"), 1.0, 0.5, 0.5);
	}

	glDrawArrays(GL_POINTS, 0, 1);

}

void CControlPoint::Move(float newX, float newY)
{
	this->X = newX;
	this->Y = newY;

	ParentCurve->ToBeUpdated = true;

	//TODO: set height as a function of terrain Height + a delta Value
}

bool CControlPoint::CheckMouseClick(SDL_Event evt)
{
	/*
	*	The point under the mousse pointer is the one inserted
	*/
	if (ContextExecution->ControlPointInserted)
	{
		/*
		*	If left click,
		*/
		if (evt.button.button == 1)
		{
			/*
			*	One click  Stop to mouve the point and add a new one
			*/
			if (evt.button.clicks == 1)
			{
				ContextExecution->ControlPointInserted = nullptr;
				ContextExecution->AddPointToSelectedCurve(nullptr);

				return false;
			}
			else
			{
				/*
				*	Double click  Stop to move the point
				*/
				ContextExecution->ControlPointInserted = nullptr;

				/*
				*	Say to the ditor that we are not longer in ADD_POINT mode
				*/
				ContextExecution->SetDefaultMode();

				return false;
			}
		}
	}
	else
	{
		/*
		*	User click on this control point, reset other to unselected state
		*/
		if (ContextExecution->SelectedPoint == nullptr)
		{
			ContextExecution->SelectedPoint = this;
		}
		else
		{
			ContextExecution->SelectedPoint->isSelected = false;
			ContextExecution->SelectedPoint = this;
		}
	}

	/*
	* If user click on one selected point, then the selected point is unset
	*/
	if (isSelected)
	{
		isSelected = false;
	}
	else
	{
		isSelected = true;
	}

	return false;
}

void CControlPoint::CheckMouseIsOver(SDL_Event evt)
{
}

void CControlPoint::CheckMouseIsLeaving(SDL_Event evt)
{
}
