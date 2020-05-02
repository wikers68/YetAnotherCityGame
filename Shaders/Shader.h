#pragma once

#include <GL/glew.h>
#include <iostream>

class CShader
{
public:
	CShader();
	~CShader();

	bool isCompiled;

	GLuint _glProgram;
	GLuint getShaderProgram(void);

	bool Compile(const char *argVertexShader, const char *argPixelShader, const char *GeometryShader = nullptr);
};

