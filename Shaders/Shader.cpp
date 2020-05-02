#include "stdafx.h"
#include "Shader.h"


CShader::CShader()
{
}


CShader::~CShader()
{
}

GLuint CShader::getShaderProgram(void)
{
	return _glProgram;
}

bool CShader::Compile(const char *argVertexShader, const char *argPixelShader, const char *GeometryShader)
{
	_glProgram = glCreateProgram();

	GLuint _vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(_vertexShader, 1, &argVertexShader, 0);
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

	glAttachShader(_glProgram, _vertexShader);

	GLuint _pixelShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(_pixelShader, 1, &argPixelShader, 0);
	glCompileShader(_pixelShader);

	glGetShaderiv(_pixelShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(_pixelShader, 512, NULL, infoLog);
		int size = -1;
		glGetShaderInfoLog(_pixelShader, 512, &size, infoLog);
		std::cout << "ERROR::SHADER::PIXEL::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	glAttachShader(_glProgram, _pixelShader);

	/*
	*	Geomtry shader compilation. Optional 
	*/
	if (GeometryShader != nullptr)
	{
		GLuint _geomShader = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(_geomShader, 1, &GeometryShader, 0);
		glCompileShader(_geomShader);

		glGetShaderiv(_geomShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(_geomShader, 512, NULL, infoLog);
			int size = -1;
			glGetShaderInfoLog(_geomShader, 512, &size, infoLog);
			std::cout << "ERROR::SHADER::GEOMETRY::COMPILATION_FAILED\n" << infoLog << std::endl;
		}
		glAttachShader(_glProgram, _geomShader);
	}

	/*
	*	Link the program to end sahder compilation
	*/
	glLinkProgram(_glProgram);

	glGetProgramiv(_glProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(_vertexShader, 512, NULL, infoLog);
		int size = -1;
		glGetProgramInfoLog(_vertexShader, 512, &size, infoLog);
		std::cout << "ERROR::SHADER::LINK_Program::FAILED\n" << infoLog << std::endl;
	}


	return true;
}