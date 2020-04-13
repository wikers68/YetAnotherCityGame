#pragma once

#include <string>
#include <map>
#include <GL/glew.h>
#include "Shader.h"
#include "ShaderSource\C3DObjectShaders.h"

class CShaderManager
{
public:

	static CShaderManager &getInstance();

	bool InitializeShader(void);

	CShader *getShader(std::string shaderName);

	bool AddShader(std::string name, const char *VertexShaderSource, const char *FragmentShaderSource);

private:
	CShaderManager();
	~CShaderManager();

	CShaderManager& operator= (const CShaderManager&) {}
	CShaderManager(const CShaderManager&) {}

	static CShaderManager instance;

	std::map<std::string, CShader*> *EnsembleShader;
};

