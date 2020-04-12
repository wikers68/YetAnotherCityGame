#include "stdafx.h"
#include "Context.h"


CContext::CContext()
{
	_GuiElements = new std::list<CGuiBaseRect*>();
}


CContext::~CContext()
{
	_GuiElements->clear();
	delete _GuiElements;
}


bool CContext::CreateContext()
{
	return false;
}


bool CContext::ActivateContext()
{
	CContextManager::Instance().SetCurrentActiveContext(this);
	return true;
}


bool CContext::RunContext(float delta_t)
{
	/*
	*	We delete the previous context after that the new one is running.
	*/
	CContextManager::Instance().DeletePreviousContext();

	ManageEvent();
	RunContextLogic(delta_t);

	return false;
}


bool CContext::DestroyContext()
{
	return false;
}

void CContext::RegisterGui_ForEvent_Handling(CGuiBaseRect * arg)
{
	this->_GuiElements->push_back(arg);
}

void CContext::ManageEvent(void)
{
	SDL_Event evt;
	while (SDL_PollEvent(&evt))
	{
		/*
		*	First, we search for all GUI elements which can receive event
		*/
		std::list<CGuiBaseRect*>::iterator it;

		for (it = _GuiElements->begin(); it != _GuiElements->end(); it++)
		{
			//only CGUiBase Rect can handle  event
			if (static_cast<CGuiBaseRect*>(*it))
			{
				if (static_cast<CGuiBaseRect*>(*it)->IsVisible())
				{
					static_cast<CGuiBaseRect*>(*it)->Generate_Mousse_Action(evt);
				}
			}

		}

		//function defined in parent class. Used to manage local event <-> Specific to active context
		EventProcessing(evt);
	}

}
