#include "stdafx.h"
#include "ShaderManager.h"

#include "ShaderSource\C3DObjectShaders.h"
#include "ShaderSource\CTerrainShaders.h"
#include "ShaderSource\CControlPointShader.h"
#include "ShaderSource\CCurveShader.h"
#include "ShaderSource\CAxis_Shader.h"
#include "ShaderSource\CTerrainCells_Heightmap_Shaders.h"

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
	if (!AddShader("CControlPoint_Shader", VertexShader_CControlPoint, FragmentShader_CControlPoint, GeomShader_CControlPoint)) return false;
	if (!AddShader("CTerrainCurve_Shader", VertexShader_CTerrainCurve, FragmentShader_CTerrainCurve, GeomShader_CTerrainCurve)) return false;
	if (!AddShader("CAxis_Shader", VertexShader_CAxis, FragmentShader_CAxis, GeomShader_CAxis)) return false;
	if (!AddShader("CTerrainCells_Heightmap_Shaders", VertexShader_CTerrainCells_Heightmap, FragmentShader_CTerrainCells_Heightmap)) return false;
	if (!AddShader("CTerrainCells_Heightmap_3D", VertexShader_CTerrainCells_Heightmap_3D, FragmentShader_CTerrainCells_Heightmap_3D)) return false;

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

bool CShaderManager::AddShader(std::string name, const char *VertexShaderSource, const char *FragmentShaderSource, const char *GeometryShader)
{
	CShader *shader = new CShader();

	if (shader->Compile(VertexShaderSource, FragmentShaderSource,GeometryShader))
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
