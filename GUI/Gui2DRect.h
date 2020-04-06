#pragma once

/*
*	Base class to draw 2D rectangle with OpenGl Command
*/
#include "GuiBaseRect.h"

#include <GL/glew.h>
#include <iostream>

#include "../Option.h"

class CGui2DRect : public CGuiBaseRect
{
public:
	CGui2DRect(int argWidth, int argHeight, int argHorizontalPosition, int argVerticalPosition);
	~CGui2DRect();

	GLuint _vertexShader;
	GLuint _pixelShader;

	GLuint _bufferVertex;
	GLuint _vertexArray;

	void Draw(void) override;

	void SetBackGroundColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha = 1.0f);

private:
	
	// background color
	 GLfloat _Red;
	 GLfloat _Green;
	 GLfloat _Blue;
	 GLfloat _Alpha;
};

