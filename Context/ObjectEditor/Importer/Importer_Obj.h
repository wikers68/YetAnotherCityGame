#pragma once

/*
*	Class return an static object, no animation
*/
#include <String>
#include <fstream>
#include <sstream>
#include <map>
#include <list>
#include <glm/glm.hpp>
#include "../../../3DGameObject/StaticObject.h"

class CImporter_Obj
{
public:
	CImporter_Obj();
	~CImporter_Obj();

	CStaticObject * ImportObjFile(std::wstring filePath);

	std::list<StaticVertex> *MeshVertexList;

private:
	void AddVertex_ToMesh(std::string vertex, std::map<int, StaticVertex*> *loadedVertex, std::map<int, glm::vec2> *loadedUV);

	CStaticObject *GenerateObject(void);

};

