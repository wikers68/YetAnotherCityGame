#include "stdafx.h"
#include "3DAssetEditor.h"


C3DAssetEditor::C3DAssetEditor()
{
	importedStaticObject = nullptr;

	Widget_Style wsTopMenuBackGround;
	wsTopMenuBackGround.hPosition = HORIZONTAL_LEFT;
	wsTopMenuBackGround.vPosition = VERTICAL_TOP;
	wsTopMenuBackGround.hSize.size = COption::getInstance().Get_Horizontal_Resolution();
	wsTopMenuBackGround.hSize.AbsOrRel = ABS_REL::_ABSOLUTE;
	wsTopMenuBackGround.vSize.size = 50;
	wsTopMenuBackGround.vSize.AbsOrRel = ABS_REL::_ABSOLUTE;
	TopMenuBackGround = new CGui2DRect(wsTopMenuBackGround);
	
	Widget_Style wsTopMenu_Layout;
	wsTopMenu_Layout.hPosition = 0;
	wsTopMenu_Layout.vPosition = 0;
	wsTopMenu_Layout.hSize.size = 100;
	wsTopMenu_Layout.hSize.AbsOrRel = ABS_REL::_RELATIVE;
	wsTopMenu_Layout.hSize.relTo = SIZE_RELATIVE_TO::PARENT;
	wsTopMenu_Layout.vSize.size = 100;
	wsTopMenu_Layout.vSize.AbsOrRel = ABS_REL::_RELATIVE;
	wsTopMenu_Layout.vSize.relTo = SIZE_RELATIVE_TO::PARENT;

	CHorizontal_layout *hl = new CHorizontal_layout(wsTopMenu_Layout, 10);
	TopMenuBackGround->AddChild(hl);


	Widget_Style wsButton;
	wsButton.hPosition = HORIZONTAL_CENTER;
	wsButton.vPosition = VERTICAL_CENTER; //TODO: bug, n'aligne pas le widget au milieu du parent
	wsButton.hSize.size = 100;
	wsButton.hSize.AbsOrRel = ABS_REL::_RELATIVE;
	wsButton.hSize.relTo = SIZE_RELATIVE_TO::PARENT;
	wsButton.vSize.size = 80;
	wsButton.vSize.AbsOrRel = ABS_REL::_RELATIVE;
	wsButton.vSize.relTo = SIZE_RELATIVE_TO::PARENT;

	Button_backGround_ImportGeom = new CGui2DRect(wsButton);
	Button_backGround_ImportGeom->SetBackGroundColor(BUTTON_BACKGROUND_OVER_COLOR);
	hl->AddChild(Button_backGround_ImportGeom);

	RegisterGui_ForEvent_Handling(Button_backGround_ImportGeom);
	Button_backGround_ImportGeom->Evenment->Set_OnClick_Callback(std::bind(&C3DAssetEditor::ImportAssetEvent, this, std::placeholders::_1));
	Button_backGround_ImportGeom->Evenment->Set_IsOver_Callback(std::bind(&C3DAssetEditor::IsOverButton, this, std::placeholders::_1));
	Button_backGround_ImportGeom->Evenment->Set_IsLeaving_Callback(std::bind(&C3DAssetEditor::IsLeavingButton, this, std::placeholders::_1));

	OpenAssetButton = new CGui2DRect(wsButton);
	OpenAssetButton->SetBackGroundColor(BUTTON_BACKGROUND_OVER_COLOR);
	hl->AddChild(OpenAssetButton);
	RegisterGui_ForEvent_Handling(OpenAssetButton);
	OpenAssetButton->Evenment->Set_OnClick_Callback(std::bind(&C3DAssetEditor::OpenwindowAssetProperties, this, std::placeholders::_1));
	OpenAssetButton->Evenment->Set_IsOver_Callback(std::bind(&C3DAssetEditor::IsOverButton, this, std::placeholders::_1));
	OpenAssetButton->Evenment->Set_IsLeaving_Callback(std::bind(&C3DAssetEditor::IsLeavingButton, this, std::placeholders::_1));

	/*
	*	Set up of the material 
	*/

	Widget_Style wsMaterialBackground;
	wsMaterialBackground.hPosition = HORIZONTAL_RIGHT;
	wsMaterialBackground.vPosition = wsTopMenuBackGround.vSize.size;
	wsMaterialBackground.hSize.size = 200;
	wsMaterialBackground.hSize.AbsOrRel = ABS_REL::_ABSOLUTE;
	wsMaterialBackground.vSize.size = COption::getInstance().Get_Vertical_Resolution() - wsTopMenuBackGround.vSize.size;
	wsMaterialBackground.vSize.AbsOrRel = ABS_REL::_ABSOLUTE;

	materialBackground = new CGui2DRect(wsMaterialBackground);
	CVertical_layout *vlMaterial = new CVertical_layout(wsTopMenu_Layout, 10);
	materialBackground->AddChild(vlMaterial);

	materialBaseColorButton = new CGui2DRect(wsButton);
	materialBaseColorButton->SetBackGroundColor(BUTTON_BACKGROUND_OVER_COLOR);
	materialBaseColorButton->Evenment->Set_OnClick_Callback(std::bind(&C3DAssetEditor::ImportBaseColorTexture, this, std::placeholders::_1));
	materialBaseColorButton->Evenment->Set_IsOver_Callback(std::bind(&C3DAssetEditor::IsOverButton, this, std::placeholders::_1));
	materialBaseColorButton->Evenment->Set_IsLeaving_Callback(std::bind(&C3DAssetEditor::IsLeavingButton, this, std::placeholders::_1));
	RegisterGui_ForEvent_Handling(materialBaseColorButton);

	materialBaseColorTexture = new CGuiTextureRect(wsButton);
	materialBaseColorTexture->SetTexture(nullptr); // display nothing at start up
	materialBaseColorButton->AddChild(materialBaseColorTexture);

	vlMaterial->AddChild(materialBaseColorButton);

	/*windowAssetProperties = new CGuiWindow("500p", "300p", HORIZONTAL_CENTER,VERTICAL_CENTER);
	windowAssetProperties->SetTitle(L"Asset Properties");
	windowAssetProperties->Hide();

	CVertical_layout *vl_windowsAssetProperties = new CVertical_layout("100%", "100%", HORIZONTAL_LEFT, VERTICAL_TOP);
	windowAssetProperties->wAddChild(vl_windowsAssetProperties);*/

	/*
	*	Create a line to display and edit asset type
	*/
	/*CHorizontal_layout *hl_AssetType = new CHorizontal_layout("100%", "100%", HORIZONTAL_CENTER, VERTICAL_CENTER);
	vl_windowsAssetProperties->AddChild(hl_AssetType);
	CDisplayText *AssetType = new CDisplayText("100%", "50p", HORIZONTAL_CENTER, VERTICAL_TOP);
	AssetType->SetText(L"Type of Asset");
	hl_AssetType->AddChild(AssetType);*/
		/*
		*	Display the type of the current asset
		*/
		/*CDisplayText *CurrentAssetType = new CDisplayText("100%", "50p", HORIZONTAL_CENTER, VERTICAL_TOP);
		CurrentAssetType->SetText(Convert_GameEntity_CategoryToWstring(GameEntity_Category::UNDEFINED));
		hl_AssetType->AddChild(CurrentAssetType);*/
}


C3DAssetEditor::~C3DAssetEditor()
{
}

void C3DAssetEditor::RunContextLogic(float delta_t)
{
	TopMenuBackGround->Draw();
	materialBackground->Draw();
	//windowAssetProperties->Draw();

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
