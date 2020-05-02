#pragma once

#include <map>
#include "GL/glew.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../../Event/EventTarget.h"
#include "ControlPoint.h"
#include "../../Context/TerrainEditor/TerrainEditor.h"

/*
*	Hold curve point data
*/
struct CCurvePoint
{
	glm::vec3 position;
};

class CTerrainEditor;
class CControlPoint;

class CTerrainCurve : public CEventTarget
{
public:
	CTerrainCurve(CTerrainEditor *ContextExecution);
	~CTerrainCurve();

	CTerrainEditor *ContextExecution;

	int LastID_ControlPoint;

	std::map<int, CControlPoint*> *SetOfControlPoint;

	/*
	*	True if user select the curve and edit it
	*/
	bool isSelected;

	/*int NumberOfVertex;

	/*
	*	true if buffer with point position need to be rebuild
	*/
	bool ToBeUpdated;

	GLuint VertexArray;
	GLuint VertexBuffer;

	void AddControlPoint(CControlPoint* arg);

	void Draw(CCamera *activeCamera);

	/*
	*	If we need to rebuild the vertex buffer after an update of one child point
	*/
	void RebuildVertexBuffer(void);

	void DeleteSelectedPoint(void);


	// Inherited via CEventTarget
	virtual bool CheckMouseClick(SDL_Event evt) override;
	virtual void CheckMouseIsOver(SDL_Event evt) override;
	virtual void CheckMouseIsLeaving(SDL_Event evt) override;
};

