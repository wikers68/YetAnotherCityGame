#pragma once

#include "GL/glew.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../../Camera/Camera.h"
#include "../../Shaders/ShaderManager.h"
#include "../../Event/EventTarget.h"
#include "../../Context/TerrainEditor/TerrainEditor.h"
#include "../../Utilities/MovableObject.h"

/*
*	Structure defining an OpenGL vertex specific to draw COntrol point
*/
struct COntrolPointGL
{
	glm::vec3 position;
};

class CTerrainEditor;
class CTerrainCurve;
class CMovableObject;

class CControlPoint : public CEventTarget, public CMovableObject
{
public:
	CControlPoint(CTerrainEditor *ContextExecution, CTerrainCurve *CurveOwner);
	~CControlPoint();

	CTerrainEditor *ContextExecution;
	CTerrainCurve *ParentCurve;

	/*
	*	Position of point in space
	*/
	//float X, Y, height; 

	bool isSelected;

	/*
	*/
	void Draw(CCamera *activeCamera);

	void Move(float newX, float newY);

	GLuint vertexArray;

	// Inherited via CEventTarget
	virtual bool CheckMouseClick(SDL_Event evt) override;
	virtual void CheckMouseIsOver(SDL_Event evt) override;
	virtual void CheckMouseIsLeaving(SDL_Event evt) override;
};

