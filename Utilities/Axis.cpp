#include "stdafx.h"
#include "Axis.h"

#include "../Terrain/Modeling/ControlPoint.h"

CAxis::CAxis(CMovableObject *parent, AXIS direction) : CEventTarget()
{
	ParentObject = parent;

	Direction = direction;

	glGenVertexArrays(1, &VertexArray);
	glBindVertexArray(VertexArray);

	CAxisVertex v1;
	v1.position.x = 0.0f;
	v1.position.y = 0.0f;
	v1.position.z = 0.0f;

	CAxisVertex v2;
	v2.position.x = 0.0f;
	v2.position.y = 0.0f;
	v2.position.z = 0.0f;

	switch (Direction)
	{
	case AXIS::X:
		v2.position.x = 1.0f;
		break;
	case AXIS::Y:
		v2.position.y = 1.0f;
		break;
	case AXIS::Z:
		v2.position.z = 1.0f;
		break;
	}

	CAxisVertex *bufferData = (CAxisVertex*)calloc(2, sizeof(CAxisVertex));
	bufferData[0] = v1;
	bufferData[1] = v2;

	/*
	*	Create an empty buffer, will be fill later
	*/
	glGenBuffers(1, &VertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, 2 * sizeof(CAxisVertex), bufferData, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	isSelected = false;

	yp = 0;
}


CAxis::~CAxis()
{
}

void CAxis::Draw(CCamera *activeCamera)
{

	glBindVertexArray(VertexArray);

	GLuint shaderProg = CShaderManager::getInstance().getShader("CAxis_Shader")->getShaderProgram();
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

	glUniform3f(glGetUniformLocation(shaderProg, "PointWorldPosition"), ParentObject->X, ParentObject->Y, ParentObject->Height);

	if (isSelected)
	{
		glUniform3f(glGetUniformLocation(shaderProg, "Color"), 0.0, 1.0, 0.3);
	}
	else
	{
		glUniform3f(glGetUniformLocation(shaderProg, "Color"), 0.0, 0.3, 1.0);
	}

	glDrawArrays(GL_LINE_STRIP, 0,2);

}


bool CAxis::CheckMouseClick(SDL_Event evt)
{
	isSelected = true;
	
	
	return false;
}

void CAxis::CheckMouseIsOver(SDL_Event evt)
{
	if (isSelected)
	{
		int y = evt.motion.y;

		if (yp == 0)
		{
			yp = y;
		}
		else
		{
			int delta_y = y - yp;
			yp = y;

			this->ParentObject->Height -= (float)delta_y / 100.0f;

			/*
			*	If the parent is a ControlPoint, we need to update the Curve parent with new point position
			*/
			if (static_cast<CControlPoint*>(ParentObject))
			{
				static_cast<CControlPoint*>(ParentObject)->ParentCurve->ToBeUpdated = true;
			}
		}
	}
}

void CAxis::CheckMouseIsLeaving(SDL_Event evt)
{
	isSelected = false;
}

void CAxis::Mouse_Button_Up(SDL_Event evt)
{
	isSelected = false;
}
