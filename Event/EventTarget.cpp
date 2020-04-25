#include "stdafx.h"
#include "EventTarget.h"


CEventTarget::CEventTarget()
{
	Id = 0;
}


CEventTarget::~CEventTarget()
{
}

void CEventTarget::setId(int arg)
{
	this->Id = arg;
}

int CEventTarget::getId(void)
{
	return Id;
}
