#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../3DContext.h"
#include "../../GUI/CommonGUIheader.h"
#include "../../Terrain/Modeling/TerrainCurve.h"

enum TERRAIN_MODE
{
	NO_MODE,
	ADD_POINT_TO_CURVE,
	MOVE_POINT,
};

class CTerrainCurve;
class CControlPoint;

class CTerrainEditor : 	public C3DContext
{
public:
	CTerrainEditor();
	~CTerrainEditor();

	CBarButton *TopMenuBar;

	/*
	*	pointer to the selected curve
	*/
	CTerrainCurve *SelectedCurve;

	/*
	*	Point to the last point added by user
	*/
	CControlPoint *ControlPointInserted;
	CControlPoint *SelectedPoint;

	TERRAIN_MODE editorMode;

	virtual void RunContextLogic(float delta_t = 0.0f) override;

	virtual void OnClickScreen(int Px, int Py, float delta_t = 0.0f) override;
	virtual void MousseOnScreen(int Px, int Py, float delta_t = 0.0f) override;

	void CTerrainEditor::IsOverButton(CGui2DRect * caller);
	void CTerrainEditor::IsLeavingButton(CGui2DRect * caller);
	void CTerrainEditor::CreateNewTerrain(CGui2DRect * caller);
	void CTerrainEditor::AddCurve(CGui2DRect * caller);

	/*
	*	If a curve is selected, we can add a point at end;
	*/
	void AddPointToSelectedCurve(CGui2DRect * caller);

	void CTerrainEditor::DeletePoint(CGui2DRect * caller);

	void CTerrainEditor::MovePoint(CGui2DRect * caller);

	glm::vec3 ScreenToWorldPosition(int Px, int Py);

	CTerrainCurve *debugCurve;
};

