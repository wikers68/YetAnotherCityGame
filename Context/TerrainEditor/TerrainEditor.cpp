#include "stdafx.h"
#include "TerrainEditor.h"


CTerrainEditor::CTerrainEditor() : C3DContext()
{
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

	this->Attach_Gui_Element(TopMenuBar);
}


CTerrainEditor::~CTerrainEditor()
{
}

void CTerrainEditor::RunContextLogic(float delta_t)
{

	C3DContext::RunContextLogic(delta_t);

}

void CTerrainEditor::CreateNewTerrain(CGui2DRect * caller)
{
	this->gameTErrain = new CTerrain();
	gameTErrain->InitGrid(10);
	gameTErrain->masterCells->SetSquareSize(5);
}

void CTerrainEditor::IsOverButton(CGui2DRect * caller)
{
	caller->SetBackGroundColor(BUTTON_BACKGROUND_IsOVER_COLOR);
}

void CTerrainEditor::IsLeavingButton(CGui2DRect * caller)
{
	caller->SetBackGroundColor(BUTTON_BACKGROUND_OVER_COLOR);
}
