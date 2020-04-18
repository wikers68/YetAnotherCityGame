#include "stdafx.h"
#include "3DAssetEditor.h"


C3DAssetEditor::C3DAssetEditor()
{
	TopMenuBackGround = new CGui2DRect(CGuiBaseRect::ConvertIntToCommandeSring(COption::getInstance().Get_Horizontal_Resolution(),"p"),"50p", 0, 0);
	
	CHorizontal_layout *hl = new CHorizontal_layout("100%", "80%", 0, 5, 10);
	TopMenuBackGround->AddChild(hl);

	Button_backGround_ImportGeom = new CGui2DRect("50p", "100%", 0, 0);
	Button_backGround_ImportGeom->SetBackGroundColor(BUTTON_BACKGROUND_OVER_COLOR);
	hl->AddChild(Button_backGround_ImportGeom);

	RegisterGui_ForEvent_Handling(Button_backGround_ImportGeom);
	Button_backGround_ImportGeom->Evenment->Set_OnClick_Callback(std::bind(&C3DAssetEditor::ImportAssetEvent, this, std::placeholders::_1));
	Button_backGround_ImportGeom->Evenment->Set_IsOver_Callback(std::bind(&C3DAssetEditor::IsOverButton, this, std::placeholders::_1));
	Button_backGround_ImportGeom->Evenment->Set_IsLeaving_Callback(std::bind(&C3DAssetEditor::IsLeavingButton, this, std::placeholders::_1));
}


C3DAssetEditor::~C3DAssetEditor()
{
}

void C3DAssetEditor::RunContextLogic(float delta_t)
{
	C3DContext::RunContextLogic(delta_t);

	TopMenuBackGround->Draw();
}

void C3DAssetEditor::EventProcessing(SDL_Event evt, float delta_t)
{
	C3DContext::EventProcessing(evt, delta_t);
}

void C3DAssetEditor::ImportAssetEvent(CGui2DRect * caller)
{
	CFileDialog *fd;
}

void C3DAssetEditor::IsOverButton(CGui2DRect * caller)
{
	caller->SetBackGroundColor(BUTTON_BACKGROUND_IsOVER_COLOR);
}

void C3DAssetEditor::IsLeavingButton(CGui2DRect * caller)
{
	caller->SetBackGroundColor(BUTTON_BACKGROUND_OVER_COLOR);
}