#include "stdafx.h"
#include "MovableObject.h"


CMovableObject::CMovableObject()
{
	X = Y = Height = 0.0f;

	Height_Axis = new CAxis(this, AXIS::Z);
	CContextManager::Instance().GetCurrentActiveContext()->RegisterGui_ForEvent_Handling(Height_Axis);
}


CMovableObject::~CMovableObject()
{
}

void CMovableObject::DrawAxis(CCamera *activeCamera, float delta_t)
{
	Height_Axis->Draw(activeCamera);
}

glm::vec3 CMovableObject::getVec3(void)
{
	return glm::vec3(X,Y,Height);
}
