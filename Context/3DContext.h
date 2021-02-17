#ifndef C3DCONTEXT_H
#define C3DCONTEXT_H

#include "Context.h"
#include "../3DGameObject/StaticObject.h"
#include "../Camera/Camera.h"
#include "../GUI/CommonGUIheader.h"
#include "../Terrain/Terrain.h"

class CTerrain;

class C3DContext : public CContext
{
public:
	C3DContext();
	~C3DContext();

	// Inherited via CContext
	virtual void RunContextLogic(float delta_t = 0.0f) override;
	virtual void EventProcessing(SDL_Event evt, float delta_t = 0.0) override;

	CStaticObject *debugObject;

	CCamera *camera;

	/*
	*	3D context can display one terrain
	*/
	CTerrain *gameTErrain;

	/*
	*	Use to add child to masterWidget as the class is private
	*/
	void Attach_Gui_Element(CGuiBaseRect *child);

private:

	//an invisible widget in which we will add all GUi children
	CEmptySlot *masterWidget;

};
#endif // !C3DCONTEXT_H


