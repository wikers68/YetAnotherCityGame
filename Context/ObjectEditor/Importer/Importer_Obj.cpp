#include "stdafx.h"
#include "Importer_Obj.h"


CImporter_Obj::CImporter_Obj()
{
	MeshVertexList = new std::list<StaticVertex>();
}


CImporter_Obj::~CImporter_Obj()
{
}

CStaticObject * CImporter_Obj::ImportObjFile(std::wstring filePath)
{
	std::fstream file;

	/*
	*	Open in read mode only
	*/
	file.open(filePath.c_str(), std::fstream::in);

	/*
	*	If opening failed, display a message
	*/
	if (!file.is_open())
	{
		std::wcout << L"Can't open file: " << filePath << std::endl;
		return nullptr;
	}

	std::string line;

	/*
	*	Vertex that we will create
	*/
	StaticVertex *vt;
	int vertexNumber = -1;
	int uvNumber = -1;

	/*
	*	Map of all vertex read from file
	*/
	std::map<int, StaticVertex*> *vertex = new std::map<int, StaticVertex*>();
	std::map<int,glm::vec2> *uvList = new std::map<int,glm::vec2>();

	while (std::getline(file, line))
	{
		/*
		*	we split line with "blank" character to parse element
		*/

		std::string SubString;
		std::istringstream line_Stream(line);

		/*
		*	count the position in the line split
		*/
		int positionInLine = 0;

		/*
		*	Current line type
		*/
		bool isVertexPosition = false;
		bool isVertexUv = false;
		bool isFace = false;

		/*
		*	Extract for first letter to know what type data line is containing
		*/
		while (std::getline(line_Stream, SubString, ' '))
		{
			/*
			*	 Line starting with "v" are vertex position
			*/

			switch (positionInLine)
			{
			case 0:
				if (SubString.compare("v") == 0)
				{
					vertexNumber++;
					vt = new StaticVertex();
					isVertexPosition = true;
					vertex->insert(std::pair<int, StaticVertex*>(vertexNumber,vt));
				}
				if (SubString.compare("vt") == 0)
				{
					uvNumber++;
					isVertexUv = true;
					uvList->insert(std::pair<int, glm::vec2>(uvNumber, glm::vec2()));
				}
				if (SubString.compare("f") == 0)
				{
					isFace = true;
				}
				break;
			case 1:
				if (isVertexPosition)
				{
					vt->position.x = std::atof(SubString.c_str());
				}
				if (isVertexUv)
				{
					if (uvList->find(uvNumber) != uvList->end())
					{
						uvList->find(uvNumber)->second.x = std::atof(SubString.c_str());
					}
				}

				break;
			case 2:
				if (isVertexPosition)
				{
					vt->position.y = std::atof(SubString.c_str());
				}
				if (uvList->find(uvNumber) != uvList->end())
				{
					uvList->find(uvNumber)->second.y = std::atof(SubString.c_str());
				}
				break;
			case 3:
				if (isVertexPosition)
				{
					vt->position.z = std::atof(SubString.c_str());
				}
				break;
			default: break;
			}

			/*
			*	Same command for three face description
			*	sample: f 12/1/1 5/2/1 7/3/1 10/4/1
			*/
			if (isFace && positionInLine > 0)
			{
				AddVertex_ToMesh(SubString, vertex, uvList);
			}

			positionInLine++;
		}

	}

	file.close();

	return GenerateObject();
}

void CImporter_Obj::AddVertex_ToMesh(std::string vertex, std::map<int, StaticVertex*>* loadedVertex, std::map<int, glm::vec2>* loadedUV)
{
	/*
	*	Vertex data is (in order):
	*		- vertex ID,
	*		- uv id,
	*		- map ID
	*/
	std::string VertexData;

	/*
	*	we split the vertex data with "/" as delimiter
	*/
	std::istringstream VertexData_Stream(vertex);

	int position = 0;

	int vertexPositionID = 0;
	int vertexUV_Id = 0;
	int vertexNormalId = 0; 

	while (std::getline(VertexData_Stream,VertexData,'/'))
	{
		switch (position)
		{
		case 0:
			vertexPositionID = std::atoi(VertexData.c_str());
			break;
		case 1:
			vertexUV_Id = std::atoi(VertexData.c_str());
			break;
		case 2:
			vertexNormalId = std::atoi(VertexData.c_str());
			break;
		}

		position++;
	}

	StaticVertex *v = new StaticVertex();

	/*
	*	C++ element index start at 0 but obj object at 1
	*/
	int vertexPositionID_Offset = vertexPositionID - 1;

	if (loadedVertex->find(vertexPositionID_Offset) != loadedVertex->end())
	{
		v->position = loadedVertex->find(vertexPositionID_Offset)->second->position;
	}

	int vertexUV_IdOffset = vertexUV_Id - 1;

	if (loadedUV->find(vertexUV_IdOffset) != loadedUV->end())
	{
		v->uv0 = loadedUV->find(vertexUV_IdOffset)->second;
	}

	/*
	*	Copy vertex to the list containing all vertex
	*/
	this->MeshVertexList->push_front(*v);

	delete v;
}

CStaticObject * CImporter_Obj::GenerateObject(void)
{
	int numberOfVertex = this->MeshVertexList->size();

	StaticVertex *v = (StaticVertex*)calloc(numberOfVertex, sizeof(StaticVertex));

	std::list<StaticVertex>::iterator it;

	int position = 0;
	for (it = this->MeshVertexList->begin(); it != this->MeshVertexList->end(); it++)
	{
		v[position] = (*it);
		position++;
	}

	CStaticObject *resultat = new CStaticObject();
	resultat->Initialize(v, numberOfVertex);

	return resultat;
}
