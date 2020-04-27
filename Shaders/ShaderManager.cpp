#include "stdafx.h"
#include "ShaderManager.h"

CShaderManager CShaderManager::instance = CShaderManager();

CShaderManager & CShaderManager::getInstance()
{
	return instance;
}

bool CShaderManager::InitializeShader(void)
{
	EnsembleShader = new std::map<std::string, CShader*>();

	if (!AddShader("CStaticObject_Shader", VertexShader_StaticObject, FragmentShader_StaticObject)) return false;
	if (!AddShader("CTerrain_Shader", VertexShader_CTerrain, FragmentShader_CTerrain)) return false;

	return true;
}

CShader * CShaderManager::getShader(std::string shaderName)
{

	if (EnsembleShader)
	{
		std::map<std::string,CShader*>::iterator results = EnsembleShader->find(shaderName);

		if (results != EnsembleShader->end())
		{
			return results->second;
		}
		else
		{
			/*
			*	Shader doesn't exist in mao
			*/
			return nullptr;
		}
	}

	return nullptr;
}

bool CShaderManager::AddShader(std::string name, const char *VertexShaderSource, const char *FragmentShaderSource)
{
	CShader *shader = new CShader();

	if (shader->Compile(VertexShaderSource, FragmentShaderSource))
	{
		if (EnsembleShader)
		{
			EnsembleShader->insert(std::pair<std::string,CShader*>(name,shader));
			return true;
		}
	}

	return false;
}

CShaderManager::CShaderManager()
{
	EnsembleShader = nullptr;
}


CShaderManager::~CShaderManager()
{
}
