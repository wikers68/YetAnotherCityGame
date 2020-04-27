#pragma once
#include "../3DContext.h"
#include "../../GUI/CommonGUIheader.h"

class CTerrainEditor : 	public C3DContext
{
public:
	CTerrainEditor();
	~CTerrainEditor();

	CBarButton *TopMenuBar;

	virtual void RunContextLogic(float delta_t = 0.0f) override;

	void CTerrainEditor::IsOverButton(CGui2DRect * caller);
	void CTerrainEditor::IsLeavingButton(CGui2DRect * caller);
	void CTerrainEditor::CreateNewTerrain(CGui2DRect * caller);

};

