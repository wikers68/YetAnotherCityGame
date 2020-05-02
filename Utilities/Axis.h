#pragma once

#include <map>
#include "GL/glew.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../../Event/EventTarget.h"
#include "../Camera/Camera.h"
#include "../Shaders/ShaderManager.h"
#include "MovableObject.h"

class CMovableObject;

enum AXIS
{
	X,
	Y,
	Z,
};

/*
*	Hold curve point data
*/
struct CAxisVertex
{
	glm::vec3 position;
};

class CAxis : public CEventTarget
{
public:
	CAxis(CMovableObject *parent, AXIS direction);
	~CAxis();

	/*
	*	Object that will be move along this axis
	*/
	CMovableObject *ParentObject;

	AXIS Direction;

	/*
	*	True if user select the curve and edit it
	*/
	bool isSelected;


	GLuint VertexArray;
	GLuint VertexBuffer;

	void Draw(CCamera *activeCamera);

	int yp;

	// Inherited via CEventTarget
	virtual bool CheckMouseClick(SDL_Event evt) override;
	virtual void CheckMouseIsOver(SDL_Event evt) override;
	virtual void CheckMouseIsLeaving(SDL_Event evt) override;
};

