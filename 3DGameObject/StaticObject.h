#pragma once

#include <glm/glm.hpp>

#include "C3DObject.h"

struct StaticVertex
{
	glm::vec3 position;
	glm::vec2 uv0;
};

class CStaticObject : public C3DObject
{
public:
	CStaticObject();
	~CStaticObject();

	void Draw(float delta_t = 0.0f) override;

	// Inherited via C3DObject
	virtual void Initialize(void * data) override;
};

