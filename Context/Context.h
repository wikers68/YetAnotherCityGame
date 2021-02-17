#pragma once

/*
*	Base class to manage game context such as main menu, in game logic, terrain editor, asset...
*/

#include <SDL.h> //for event handling
#include <list>
#include <map>

#include "../GUI/GuiBaseRect.h"
#include "../GUI/Gui2DRect.h"
#include "ContextManager.h"
#include "../Event/EventTarget.h"

class CContext
{
public:
	CContext();
	~CContext();

	std::list<CGuiBaseRect*> *_GuiElements;
	
	/*
	*	MAP containing all element of the context which can receive event
	*/
	std::map<int, CEventTarget*> *EventTargets;

	virtual bool CreateContext();
	bool ActivateContext();
	virtual void RunContextLogic(float delta_t = 0.0f) = 0;
	
	/*
	*	Function executed by Context manager when mousse click is captured but not treated by a Gui or gameElement
	*/
	virtual void OnClickScreen(int Px, int Py, float delta_t = 0.0f) {};

	virtual void ManageOnClickEvent(SDL_Event evt, CEventTarget *objectClick) {};

	/*
	*	Perfom action when mousse is somewhere on screen
	*/
	virtual void MousseOnScreen(int Px, int Py, float delta_t = 0.0f) {};

	bool RunContext(float delta_t = 0.0f);
	bool DestroyContext();

	//dispatch event inside the context
	void ManageEvent(float delta_t = 0.0f, GLuint  _Object_ID_Buffer = -1 );

	void ManageMousseEvent(SDL_Event evt, float delta_t);

	virtual void EventProcessing(SDL_Event evt, float delta_t = 0.0f) = 0;

	//give an unique ID to each object that will received event
	int Free_Object_ID;

	void RegisterGui_ForEvent_Handling(/*CGuiBaseRect *arg*/ CEventTarget *evt = nullptr);

	template<class C>
	void ChangeContext(CContext *currentContext)
	{
		C *nContext = new C();

		if (static_cast<CContext*>(nContext))
		{
			nContext->CreateContext();
			nContext->ActivateContext();

			//~currentContext(); //does it works ? Not sure
		}
	}

private:

	/*
	*	We will store ID_Object from the rendering buffer. We will use value to search
	*	the EventTarget under the mousse cursor.
	*/
	int *ID_Buffer;

	/*
	*	ID du dernier objet sur lequel il y a eu un évenement
	*/
	int ID_LastObject;
};
