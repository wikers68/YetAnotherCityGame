#include "stdafx.h"
#include "StaticObject.h"


CStaticObject::CStaticObject()
{
}


CStaticObject::~CStaticObject()
{
}

void CStaticObject::Draw(float delta_t)
{
	if (!glIsEnabled(GL_DEPTH_TEST))
	{
		glEnable(GL_DEPTH_TEST);
	}

	glm::mat4 model = glm::mat4(1.0f);

	glBindVertexArray(_vertexArray);
	glUniformMatrix4fv(glGetUniformLocation(_Shader->getShaderProgram(), "Model"), 1, GL_FALSE, glm::value_ptr(model));

	if (this->ObjectMaterial->baseColorTexture)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, ObjectMaterial->baseColorTexture->getGlTexture());
	}

	glDrawArrays(GL_TRIANGLES, 0, numberOfvertex);
}

void CStaticObject::Initialize(void * data, int numberOfElement)
{

	this->numberOfvertex = numberOfElement;

	glGenVertexArrays(1, &_vertexArray);
	glBindVertexArray(_vertexArray);

	GLuint vertexBuffer;
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, numberOfElement * sizeof(StaticVertex), data, GL_STATIC_DRAW);

	/*
	*	Note: always place this after puting data in the buffer. At least, before gLDrawsArrays...;
	*/
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(StaticVertex), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(StaticVertex), (void*)(1 * sizeof(glm::vec3)));
	glEnableVertexAttribArray(1);

	_Shader = CShaderManager::getInstance().getShader("CStaticObject_Shader");

}
