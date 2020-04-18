#pragma once

#include<afxdlgs.h>

#include "../3DContext.h"
#include "../../3DGameObject/StaticObject.h"
#include "../../Camera/Camera.h"
#include "../../GUI/Layout/Horizontal_layout.h"
#include "../../GUI/GUI_Style.h"

/*
*	Include for importer
*/
#include "Importer\Importer_Obj.h"

class C3DAssetEditor : public C3DContext
{
public:
	C3DAssetEditor();
	~C3DAssetEditor();

	// Inherited via CContext
	virtual void RunContextLogic(float delta_t = 0.0f) override;
	virtual void EventProcessing(SDL_Event evt, float delta_t = 0.0) override;

	CGui2DRect *TopMenuBackGround;

	CGui2DRect *Button_backGround_ImportGeom;

	CStaticObject *importedStaticObject;

	/*
	*	Open a File Dialog box, let the user to choose the asset to be imported.
	*	Then start the import process
	*/
	void ImportAssetEvent(CGui2DRect *caller);

	void IsOverButton(CGui2DRect *caller);
	void IsLeavingButton(CGui2DRect * caller);

};

