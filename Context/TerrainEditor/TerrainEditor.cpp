#include "stdafx.h"
#include "TerrainEditor.h"


CTerrainEditor::CTerrainEditor() : C3DContext()
{

	editorMode = TERRAIN_MODE::NO_MODE;

	TopMenuBar = new CBarButton(50);

	CGui2DRect *bt;

	bt = TopMenuBar->AddTextualButton(L"New");
	bt->Evenment->Set_OnClick_Callback(std::bind(&CTerrainEditor::CreateNewTerrain,this,std::placeholders::_1));
	bt->Evenment->Set_IsOver_Callback(std::bind(&CTerrainEditor::IsOverButton, this, std::placeholders::_1));
	bt->Evenment->Set_IsLeaving_Callback(std::bind(&CTerrainEditor::IsLeavingButton, this, std::placeholders::_1));
	RegisterGui_ForEvent_Handling(bt);

	bt = TopMenuBar->AddTextualButton(L"Open");
	bt->Evenment->Set_IsOver_Callback(std::bind(&CTerrainEditor::IsOverButton, this, std::placeholders::_1));
	bt->Evenment->Set_IsLeaving_Callback(std::bind(&CTerrainEditor::IsLeavingButton, this, std::placeholders::_1));
	RegisterGui_ForEvent_Handling(bt);

	bt = TopMenuBar->AddTextualButton(L"Save");
	bt->Evenment->Set_IsOver_Callback(std::bind(&CTerrainEditor::IsOverButton, this, std::placeholders::_1));
	bt->Evenment->Set_IsLeaving_Callback(std::bind(&CTerrainEditor::IsLeavingButton, this, std::placeholders::_1));
	RegisterGui_ForEvent_Handling(bt);

	bt = TopMenuBar->AddTextualButton(L"Add Curve");
	bt->Evenment->Set_OnClick_Callback(std::bind(&CTerrainEditor::AddCurve, this, std::placeholders::_1));
	bt->Evenment->Set_IsOver_Callback(std::bind(&CTerrainEditor::IsOverButton, this, std::placeholders::_1));
	bt->Evenment->Set_IsLeaving_Callback(std::bind(&CTerrainEditor::IsLeavingButton, this, std::placeholders::_1));
	RegisterGui_ForEvent_Handling(bt);

	bt = TopMenuBar->AddTextualButton(L"Add Point");
	bt->Evenment->Set_OnClick_Callback(std::bind(&CTerrainEditor::AddPointToSelectedCurve, this, std::placeholders::_1));
	bt->Evenment->Set_IsOver_Callback(std::bind(&CTerrainEditor::IsOverButton, this, std::placeholders::_1));
	bt->Evenment->Set_IsLeaving_Callback(std::bind(&CTerrainEditor::IsLeavingButton, this, std::placeholders::_1));
	RegisterGui_ForEvent_Handling(bt);

	bt = TopMenuBar->AddTextualButton(L"Move Point");
	bt->Evenment->Set_OnClick_Callback(std::bind(&CTerrainEditor::MovePoint, this, std::placeholders::_1));
	bt->Evenment->Set_IsOver_Callback(std::bind(&CTerrainEditor::IsOverButton, this, std::placeholders::_1));
	bt->Evenment->Set_IsLeaving_Callback(std::bind(&CTerrainEditor::IsLeavingButton, this, std::placeholders::_1));
	RegisterGui_ForEvent_Handling(bt);

	bt = TopMenuBar->AddTextualButton(L"Delete Point");
	bt->Evenment->Set_OnClick_Callback(std::bind(&CTerrainEditor::DeletePoint, this, std::placeholders::_1));
	bt->Evenment->Set_IsOver_Callback(std::bind(&CTerrainEditor::IsOverButton, this, std::placeholders::_1));
	bt->Evenment->Set_IsLeaving_Callback(std::bind(&CTerrainEditor::IsLeavingButton, this, std::placeholders::_1));
	RegisterGui_ForEvent_Handling(bt);

	this->Attach_Gui_Element(TopMenuBar);

//	debugCurve = nullptr;

	//debugCurve = new CTerrainCurve(this);
	/*CControlPoint *pt1 = new CControlPoint(this,debugCurve);

	CControlPoint *pt2 = new CControlPoint(this, debugCurve);
	pt2->Y = 3.0;

	CControlPoint *pt3 = new CControlPoint(this, debugCurve);
	pt3->X = 3.0;
	pt3->Y = 3.0;

	debugCurve->AddControlPoint(pt1);
	debugCurve->AddControlPoint(pt2);
	debugCurve->AddControlPoint(pt3);

	RegisterGui_ForEvent_Handling(debugCurve);*/

	SetOfTerrainCurve = new std::list<CTerrainCurve*>();

	SelectedCurve = nullptr;
	ControlPointInserted = nullptr;
	SelectedPoint = nullptr;
}


CTerrainEditor::~CTerrainEditor()
{
}

void CTerrainEditor::RunContextLogic(float delta_t)
{
	//this->Update_Heightmap();

	C3DContext::RunContextLogic(delta_t);

	if (SetOfTerrainCurve->size() > 0)
	{
		std::list<CTerrainCurve*>::iterator it;

		for (it = SetOfTerrainCurve->begin(); it != SetOfTerrainCurve->end(); it++)
		{
			(*it)->Draw(camera);
		}
	}

}

void CTerrainEditor::OnClickScreen(int Px, int Py, float delta_t)
{
	
	switch (editorMode)
	{
	case TERRAIN_MODE::MOVE_POINT:
		editorMode = TERRAIN_MODE::NO_MODE;
		break;
	default: 
		/*
		*	First, we unselect the selected point, then a second click is needed to unselect the curve
		*/
		if (SelectedPoint)
		{
			SelectedPoint->isSelected = false;
			SelectedPoint = nullptr;
		}
		else if (SelectedCurve)
		{
			/*
			*	User doesn't want to edit the curve
			*/
			SelectedCurve->isSelected = false;
			SelectedCurve = nullptr;
		}
		break;
	}
}

void CTerrainEditor::MousseOnScreen(int Px, int Py, float delta_t)
{
	glm::vec3 MousseWorldPosition = ScreenToWorldPosition(Px, Py);

	switch (editorMode)
	{
	case TERRAIN_MODE::ADD_POINT_TO_CURVE:
		/*
		*	Move the point being inserted
		*/
		if (ControlPointInserted)
		{
			ControlPointInserted->Move(MousseWorldPosition.x, MousseWorldPosition.y);
		}
		break;
	case TERRAIN_MODE::MOVE_POINT:
		if (SelectedPoint) SelectedPoint->Move(MousseWorldPosition.x, MousseWorldPosition.y);
		break;
	default:break;
	}
}

void CTerrainEditor::ManageOnClickEvent(SDL_Event evt, CEventTarget *objectClick)
{

	switch (editorMode)
	{
	case TERRAIN_MODE::ADD_POINT_TO_CURVE:
		if (ControlPointInserted)
		{
			ControlPointInserted->CheckMouseClick(evt);
		}
		break;
	case TERRAIN_MODE::MOVE_POINT:
		if (SelectedPoint)
		{
			SelectedPoint->isSelected = false;
			SelectedPoint = nullptr;
		}
		else
		{
			objectClick->CheckMouseClick(evt);
		}
		break;
	default:
		objectClick->CheckMouseClick(evt);
		break;
	}
}

void CTerrainEditor::CreateNewTerrain(CGui2DRect * caller)
{
	this->gameTErrain = new CTerrain();
	gameTErrain->InitGrid();
	gameTErrain->masterCells->SetSquareSize(5);
}

void CTerrainEditor::AddCurve(CGui2DRect * caller)
{
	CTerrainCurve *newCurve = new CTerrainCurve(this);
	RegisterGui_ForEvent_Handling(newCurve);

	newCurve->isSelected = true;
	SelectedCurve = newCurve;

	SetOfTerrainCurve->push_back(newCurve);

	this->AddPointToSelectedCurve(nullptr);
}

void CTerrainEditor::AddPointToSelectedCurve(CGui2DRect * caller)
{
	if (SelectedCurve)
	{
		CControlPoint *cp = new CControlPoint(this,SelectedCurve);
		cp->Move(1.0, 2.0);
		SelectedCurve->AddControlPoint(cp);
		ControlPointInserted = cp;

		editorMode = TERRAIN_MODE::ADD_POINT_TO_CURVE;
	}
}

void CTerrainEditor::DeletePoint(CGui2DRect * caller)
{
	if (SelectedCurve)
	{
		SelectedCurve->DeleteSelectedPoint();
	}
}

void CTerrainEditor::MovePoint(CGui2DRect * caller)
{
	editorMode = TERRAIN_MODE::MOVE_POINT;
}

glm::vec3 CTerrainEditor::ScreenToWorldPosition(int Px, int Py)
{
	/*
	*	World coordinates of screen point, calculated in near field
	*/
	glm::vec3 screenPosition(Px, COption::getInstance().Get_Vertical_Resolution()-Py, COption::getInstance().zNearPlan);

	glm::vec3 spwc = glm::unProject(screenPosition,
		camera->getMatriceView(),
		COption::getInstance().getMatriceProjection(),
		glm::vec4(0, 0, COption::getInstance().Get_Horizontal_Resolution(), COption::getInstance().Get_Vertical_Resolution())
	);

	glm::vec3 viewDir = glm::normalize(spwc - this->camera->Position);

	/*
	*	Search for intersection with XY plan. 
	*/

	float t = - camera->Position.z / viewDir.z;

	float x = camera->Position.x + viewDir.x * t;
	float y = camera->Position.y + viewDir.y * t;

	//TODO: add terrain height in Z result

	return glm::vec3(x,y,0);
}

void CTerrainEditor::SetDefaultMode(void)
{
	editorMode = TERRAIN_MODE::NO_MODE;
}

void CTerrainEditor::Update_Heightmap(void)
{
	if (gameTErrain)
	{
		gameTErrain->UpdateHeightMap(SetOfTerrainCurve);
	}
}

void CTerrainEditor::IsOverButton(CGui2DRect * caller)
{
	caller->SetBackGroundColor(BUTTON_BACKGROUND_IsOVER_COLOR);
}

void CTerrainEditor::IsLeavingButton(CGui2DRect * caller)
{
	caller->SetBackGroundColor(BUTTON_BACKGROUND_OVER_COLOR);
}
