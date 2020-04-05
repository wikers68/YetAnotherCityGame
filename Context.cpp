#include "stdafx.h"
#include "Context.h"


CContext::CContext()
{
}


CContext::~CContext()
{
}


bool CContext::CreateContext()
{
	return false;
}


bool CContext::ActivateContext()
{
	return false;
}


bool CContext::RunContext(float delta_t)
{
	return false;
}


bool CContext::DestroyContext()
{
	return false;
}

void CContext::ManageEvent(void)
{
	SDL_Event evt;
	while (SDL_PollEvent(&evt))
	{
		EventProcessing(evt);
	}

}
