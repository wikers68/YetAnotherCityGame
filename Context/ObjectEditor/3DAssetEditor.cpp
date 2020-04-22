#include "stdafx.h"
#include "3DAssetEditor.h"


C3DAssetEditor::C3DAssetEditor()
{
	importedStaticObject = nullptr;

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

	OpenAssetButton = new CGui2DRect("50p", "100%", 0, 0);
	OpenAssetButton->SetBackGroundColor(BUTTON_BACKGROUND_OVER_COLOR);
	hl->AddChild(OpenAssetButton);
	RegisterGui_ForEvent_Handling(OpenAssetButton);
	OpenAssetButton->Evenment->Set_OnClick_Callback(std::bind(&C3DAssetEditor::OpenwindowAssetProperties, this, std::placeholders::_1));
	OpenAssetButton->Evenment->Set_IsOver_Callback(std::bind(&C3DAssetEditor::IsOverButton, this, std::placeholders::_1));
	OpenAssetButton->Evenment->Set_IsLeaving_Callback(std::bind(&C3DAssetEditor::IsLeavingButton, this, std::placeholders::_1));

	/*
	*	Set up of the material 
	*/
	materialBackground = new CGui2DRect("200p", CGuiBaseRect::ConvertIntToCommandeSring(COption::getInstance().Get_Vertical_Resolution() - 50, "p"), HORIZONTAL_RIGHT, 50);
	CVertical_layout *vlMaterial = new CVertical_layout("80%", "100%", HORIZONTAL_CENTER, 0, 10);
	materialBackground->AddChild(vlMaterial);

	materialBaseColorButton = new CGui2DRect("80%", "80%", 0, 0);
	materialBaseColorButton->Evenment->Set_OnClick_Callback(std::bind(&C3DAssetEditor::ImportBaseColorTexture, this, std::placeholders::_1));
	materialBaseColorButton->Evenment->Set_IsOver_Callback(std::bind(&C3DAssetEditor::IsOverButton, this, std::placeholders::_1));
	materialBaseColorButton->Evenment->Set_IsLeaving_Callback(std::bind(&C3DAssetEditor::IsLeavingButton, this, std::placeholders::_1));
	RegisterGui_ForEvent_Handling(materialBaseColorButton);

	materialBaseColorTexture = new CGuiTextureRect("80%", "80%", HORIZONTAL_CENTER, 0);
	materialBaseColorTexture->SetTexture(nullptr); // display nothing at start up
	materialBaseColorButton->AddChild(materialBaseColorTexture);

	vlMaterial->AddChild(materialBaseColorButton);

	windowAssetProperties = new CGuiWindow("500p", "300p", HORIZONTAL_CENTER,VERTICAL_CENTER);
	windowAssetProperties->SetTitle(L"Asset Properties");
	windowAssetProperties->Hide();

	CVertical_layout *vl_windowsAssetProperties = new CVertical_layout("100%", "100%", HORIZONTAL_LEFT, VERTICAL_TOP);
	windowAssetProperties->wAddChild(vl_windowsAssetProperties);

	/*
	*	Create a line to display and edit asset type
	*/
	CHorizontal_layout *hl_AssetType = new CHorizontal_layout("100%", "100%", HORIZONTAL_CENTER, VERTICAL_CENTER);
	vl_windowsAssetProperties->AddChild(hl_AssetType);
	CDisplayText *AssetType = new CDisplayText("100%", "50p", HORIZONTAL_CENTER, VERTICAL_TOP);
	AssetType->SetText(L"Type of Asset");
	hl_AssetType->AddChild(AssetType);
		/*
		*	Display the type of the current asset
		*/
		CDisplayText *CurrentAssetType = new CDisplayText("100%", "50p", HORIZONTAL_CENTER, VERTICAL_TOP);
		CurrentAssetType->SetText(Convert_GameEntity_CategoryToWstring(GameEntity_Category::UNDEFINED));
		hl_AssetType->AddChild(CurrentAssetType);
}


C3DAssetEditor::~C3DAssetEditor()
{
}

void C3DAssetEditor::RunContextLogic(float delta_t)
{
	TopMenuBackGround->Draw();
	materialBackground->Draw();
	windowAssetProperties->Draw();

	C3DContext::RunContextLogic(delta_t);

	if (importedStaticObject) importedStaticObject->Draw();
}

void C3DAssetEditor::EventProcessing(SDL_Event evt, float delta_t)
{
	C3DContext::EventProcessing(evt, delta_t);
}

void C3DAssetEditor::OpenwindowAssetProperties(CGui2DRect * caller)
{
	if (windowAssetProperties)
	{
		windowAssetProperties->Show();
	}
}

void C3DAssetEditor::ImportAssetEvent(CGui2DRect * caller)
{

	LPCTSTR FileFilter = L"Obj (*.obj) | *.obj";

	/*
	*	Create a MFC dialog box
	*/
	CFileDialog fd(TRUE,NULL,NULL, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST,FileFilter);

	/*
	*	Open and act if a file is selected
	*/
	if (fd.DoModal() == IDOK)
	{
		CString path = fd.GetPathName();

		CString fileExt = fd.GetFileExt();

		std::wcout << "Opening: " << (std::wstring)path << std::endl;

		if (fileExt.Compare(CString("obj")) == 0)
		{
			CImporter_Obj *objImporter = new CImporter_Obj();

			this->importedStaticObject = objImporter->ImportObjFile((std::wstring)path);
		}
	}
}

void C3DAssetEditor::IsOverButton(CGui2DRect * caller)
{
	caller->SetBackGroundColor(BUTTON_BACKGROUND_IsOVER_COLOR);
}

void C3DAssetEditor::IsLeavingButton(CGui2DRect * caller)
{
	caller->SetBackGroundColor(BUTTON_BACKGROUND_OVER_COLOR);
}

void C3DAssetEditor::ImportBaseColorTexture(CGui2DRect * caller)
{
	if (importedStaticObject)
	{
		importedStaticObject->ObjectMaterial->OpenDialogBoxToImportTexture(TextureType::BASE_COLOR);
		materialBaseColorTexture->SetTexture(importedStaticObject->ObjectMaterial->baseColorTexture);
	}
}
