#ifndef TERRAIN_CURVE_H
#define TERRAIN_CURVE_H

#include <map>
#include "GL/glew.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../../Event/EventTarget.h"
#include "ControlPoint.h"
#include "../../Context/TerrainEditor/TerrainEditor.h"
#include "../../Mesh/VertexFormat.h"

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

	/*
	*	Buffer to hold vertex used to draw line
	*/
	GLuint VertexArray_Curve;
	GLuint VertexBuffer_Curve;

	/*
	*	Buffer to hold triangle used to render heightMap
	*/
	GLuint VertexArray_TriangleHeight;
	GLuint VertexBuffer_TriangleHeight;
	int numberOfVertex_TerrainHeight;


	void AddControlPoint(CControlPoint* arg);

	void Draw(CCamera *activeCamera);

	/*
	*	Draw terrain curve height triangle as a solid in 3D view
	*/
	void DrawHeightTriangle(CCamera *activeCamera);

	/*
	*	If we need to rebuild the vertex buffer after an update of one child point
	*/
	void RebuildVertexBuffer(void);

	void DeleteSelectedPoint(void);

	void GenerateHeightRendering(void);


	// Inherited via CEventTarget
	virtual bool CheckMouseClick(SDL_Event evt) override;
	virtual void CheckMouseIsOver(SDL_Event evt) override;
	virtual void CheckMouseIsLeaving(SDL_Event evt) override;
};

#endif // !1

