#include "stdafx.h"
#include "Gui2DRect.h"


CGui2DRect::CGui2DRect(int argWidth, int argHeight, int argHorizontalPosition, int argVerticalPosition) :CGuiBaseRect(argWidth, argHeight, argHorizontalPosition, argVerticalPosition)
{
	//CGuiBaseRect(argWidth, argHeight, argHorizontalPosition, argVerticalPosition, argParent);

	glGenVertexArrays(1, &_vertexArray);
	glBindVertexArray(_vertexArray);

	float Vertex[12] =
	{
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f
	};
	
	glGenBuffers(1, &_bufferVertex);	//allocate on free buffer name

	glBindBuffer(GL_ARRAY_BUFFER, _bufferVertex);	//Create the buffer

	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex), &Vertex, GL_STATIC_DRAW);		//fill buffer with data

	//vertex format attribute. Link to the last Buffer "bind command"
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	
	const char *VertexShaderString =
	{
		"#version 420 core\n"
		"layout( location = 0) in vec2 vertexPosition;"
		"uniform ivec4 PositionSize;"
		"uniform ivec4 ScreenSize;"
		"out vec2 colorRG;"
		"void main()"
		"{"
			//dimension in viewport space of the rectangle
		"float widthRelToScreen = float(PositionSize.z) / float(ScreenSize.x);"
		"float heightRelToScreen = float(PositionSize.w) / float(ScreenSize.y);"

			//upper left corner position in screen space
		"float Xposition = -1 + 2*(vertexPosition.x * widthRelToScreen + float(PositionSize.x) / float(ScreenSize.x));"
		"float Yposition =  1 - 2*(vertexPosition.y * heightRelToScreen + float(PositionSize.y) / float(ScreenSize.y));"

			"colorRG = vec2(vertexPosition.x,vertexPosition.y);"
			"gl_Position = vec4( Xposition,Yposition,1,1);"
		"};"
	};

	const char *FragmentShaderString =
	{
		"#version 420 core\n"
		"in vec2 colorRG;"
		"out vec4 color;"
		"void main()"
		"{"
			"color = vec4( colorRG.xy,1,1);"
		"};"
	};

	_Shader = glCreateProgram();

	_vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(_vertexShader, 1, &VertexShaderString, 0);
	glCompileShader(_vertexShader);

	int  success;
	char infoLog[512];

	glGetShaderiv(_vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(_vertexShader, 512, NULL, infoLog);
		int size = -1;
		glGetShaderInfoLog(_vertexShader, 512, &size, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	glAttachShader(_Shader, _vertexShader);

	_pixelShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(_pixelShader, 1, &FragmentShaderString, 0);
	glCompileShader(_pixelShader);

	glGetShaderiv(_pixelShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(_pixelShader, 512, NULL, infoLog);
		int size = -1;
		glGetShaderInfoLog(_pixelShader, 512, &size, infoLog);
		std::cout << "ERROR::SHADER::PIXEL::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	glAttachShader(_Shader, _pixelShader);

	glLinkProgram(_Shader);

	glGetProgramiv(_Shader, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(_vertexShader, 512, NULL, infoLog);
		int size = -1;
		glGetProgramInfoLog(_vertexShader, 512, &size, infoLog);
		std::cout << "ERROR::SHADER::LINK_Program::FAILED\n" << infoLog << std::endl;
	}
}


CGui2DRect::~CGui2DRect()
{
}

void CGui2DRect::Draw(void)
{
	glUseProgram(_Shader);
	glBindVertexArray(_vertexArray);

	glUniform4i( glGetUniformLocation(_Shader, "PositionSize"),
		(GLint)CGuiBaseRect::_AbsoluteHorizontalPosition,
		(GLint)CGuiBaseRect::_AbsoluteVerticalPosition,
		(GLint)CGuiBaseRect::_Width,
		(GLint)CGui2DRect::_Height);

	glUniform4i(glGetUniformLocation(_Shader, "ScreenSize"),
		COption::getInstance().Get_Horizontal_Resolution(),
		COption::getInstance().Get_Vertical_Resolution(),
		0,
		0);
	
	glDrawArrays(GL_TRIANGLES, 0, 6);

	if (_Child)
	{
		std::list<CGuiBaseRect*>::iterator it = _Child->begin();

		for(it = _Child->begin(); it != _Child->end(); it++)
		{
			(*it)->Draw();
		}
	}
}
