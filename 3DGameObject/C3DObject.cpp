#include "stdafx.h"
#include "C3DObject.h"


C3DObject::C3DObject():CGameEntity()
{
	ObjectMaterial = new CMaterial();
}


C3DObject::~C3DObject()
{
}
