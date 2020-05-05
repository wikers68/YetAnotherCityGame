#include "stdafx.h"
#include "Context.h"


CContext::CContext()
{
	_GuiElements = new std::list<CGuiBaseRect*>();

	EventTargets = new std::map<int, CEventTarget*>();;

	Free_Object_ID = 0;
	ID_LastObject = 0;

	/*
	*	Pre Alloc memories for ID_Buffer.
	*	Buffer size = screen surface with one 32bit INT (as defined in PBR renderpass)
	*/
	ID_Buffer = (int*)calloc(COption::getInstance().Get_Horizontal_Resolution()*COption::getInstance().Get_Horizontal_Resolution(), sizeof(int));
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

void CContext::RegisterGui_ForEvent_Handling(/*CGuiBaseRect * arg,*/ CEventTarget *evt)
{
	if (evt)
	{
		Free_Object_ID++;

		evt->setId(Free_Object_ID);

		this->EventTargets->insert(std::pair<int, CEventTarget*>(evt->getId(), evt));
	}
}

void CContext::ManageEvent(float delta_t, GLuint  _Object_ID_Buffer)
{
	SDL_Event evt;
	while (SDL_PollEvent(&evt))
	{

		if (_Object_ID_Buffer > 0)
		{
			glBindTexture(GL_TEXTURE_2D, _Object_ID_Buffer);
			glGetTexImage(GL_TEXTURE_2D, 0, GL_RED_INTEGER, GL_INT, ID_Buffer);
			glBindTexture(GL_TEXTURE_2D, 0);

			if (evt.motion.x > 0 && evt.motion.y > 0 )
			{
				int mx = evt.motion.x;
				int my = COption::getInstance().Get_Vertical_Resolution() - evt.motion.y;
				int ID = -1;
				ID = ID_Buffer[mx + my*COption::getInstance().Get_Horizontal_Resolution()];

				std::map<int, CEventTarget*>::iterator it = EventTargets->find(ID);

				if (it != EventTargets->end())
				{

					CGuiBaseRect * isGui = dynamic_cast<CGuiBaseRect*>(it->second);
				
					/*
					*	Common dispatch event for all context. Only to interact with GUI
					*/

					if (isGui)
					{
						switch (evt.type)
						{
						default: break;
						case SDL_MOUSEMOTION:
							it->second->CheckMouseIsOver(evt);
							ID_LastObject = ID;
							std::cout << ID << std::endl;
							break;
						case SDL_MOUSEBUTTONDOWN:
							it->second->CheckMouseClick(evt);
							break;
						}
					}
					else //send event to non gui element
					{
						switch (evt.type)
						{
						default: break;
						case SDL_MOUSEBUTTONDOWN:
							this->ManageOnClickEvent(evt, it->second);
							break;
						case SDL_MOUSEBUTTONUP:
							it->second->Mouse_Button_Up(evt); //event action not depend of context. Event is sent to object
							break;
						case SDL_MOUSEMOTION:
							it->second->CheckMouseIsOver(evt);
							break;
						}
					}
				}
				else //user click somewhere on the screen
				{
					switch (evt.type)
					{
					default: break;
					case SDL_MOUSEBUTTONDOWN:
						if (evt.button.button == SDL_BUTTON_LEFT) //left button
						{
							this->OnClickScreen(evt.motion.x, evt.motion.y);
						}
						break;
					}
				}

				/*
				*	Mousse is moving
				*/
				MousseOnScreen(evt.motion.x, evt.motion.y, delta_t);

				if (ID != ID_LastObject)
				{
					std::map<int, CEventTarget*>::iterator LastObject = EventTargets->find(ID_LastObject);

					if (LastObject != EventTargets->end())
					{
						LastObject->second->CheckMouseIsLeaving(evt);
						ID_LastObject = 0;
					}
				}
			}
		}

		//function defined in parent class. Used to manage local event <-> Specific to active context
		EventProcessing(evt,delta_t);
	}

}
