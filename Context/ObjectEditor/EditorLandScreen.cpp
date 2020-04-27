#include "stdafx.h"
#include "EditorLandScreen.h"


CEditorLandScreen::CEditorLandScreen() : CContext()
{
	/*
	*	Common style on button
	*/
	Widget_Style wsButton;
	wsButton.hPosition = HORIZONTAL_CENTER;
	wsButton.vPosition = VERTICAL_CENTER;
	wsButton.hSize.AbsOrRel = ABS_REL::_RELATIVE;
	wsButton.hSize.relTo = SIZE_RELATIVE_TO::PARENT;
	wsButton.hSize.size = 100;
	wsButton.vSize.AbsOrRel = ABS_REL::_RELATIVE;
	wsButton.vSize.relTo = SIZE_RELATIVE_TO::PARENT;
	wsButton.vSize.size = 100;

	Widget_Style wsText;
	wsText.hPosition = HORIZONTAL_CENTER;
	wsText.vPosition = VERTICAL_CENTER;


	Widget_Style wsBackground;
	wsBackground.hPosition = HORIZONTAL_CENTER;
	wsBackground.vPosition = VERTICAL_CENTER;
	wsBackground.hSize.AbsOrRel = ABS_REL::_ABSOLUTE;
	wsBackground.hSize.size = COption::getInstance().Get_Horizontal_Resolution();
	wsBackground.vSize.AbsOrRel = ABS_REL::_ABSOLUTE;
	wsBackground.vSize.size = COption::getInstance().Get_Vertical_Resolution();

	background = new CGuiTextureRect(wsBackground);
	CTexture *_textureButton = new CTexture();
	_textureButton->LoadFromFile("../GameRessources/media/GUI/textures/background_menu_1920x1080.png");
	background->SetTexture(_textureButton);

	Widget_Style wsVerticalLayout;
	wsVerticalLayout.hPosition = 0;
	wsVerticalLayout.vPosition = 0;
	wsVerticalLayout.hSize.AbsOrRel = ABS_REL::_RELATIVE;
	wsVerticalLayout.hSize.relTo = SIZE_RELATIVE_TO::PARENT;
	wsVerticalLayout.hSize.size = 100; // % 
	wsVerticalLayout.vSize.AbsOrRel = ABS_REL::_RELATIVE;
	wsVerticalLayout.vSize.relTo = SIZE_RELATIVE_TO::PARENT;
	wsVerticalLayout.vSize.size = 100; // 

	CVertical_layout *vl = new CVertical_layout(wsVerticalLayout,20);
	background->AddChild(vl);

	CDisplayText *headText = new CDisplayText(wsText);
	headText->SetText(L"YetAnotherCityGame... Editor");
	vl->AddChild(headText);


	CHorizontal_layout *hl = new CHorizontal_layout(wsVerticalLayout, 20);
	vl->AddChild(hl);

	CGui2DRect *AssetEditorRect = new CGui2DRect(wsButton);
	AssetEditorRect->SetBackGroundColor(34.0 / 255.0, 84.0 / 255.0 , 125.0 / 255.0);
	hl->AddChild(AssetEditorRect);

	CGui2DRect *TerrainEditorRect = new CGui2DRect(wsButton);
	hl->AddChild(TerrainEditorRect);
	TerrainEditorRect->SetBackGroundColor(34.0 / 255.0, 84.0 / 255.0, 125.0 / 255.0);

	CGui2DRect *GoBackMainMenu = new CGui2DRect(wsButton);
	vl->AddChild(GoBackMainMenu);
	GoBackMainMenu->SetBackGroundColor(0.5, 0.2, 0.5);

	/*
	*	Object editor button
	*/
	CVertical_layout *vl_Object_Asset = new CVertical_layout(wsVerticalLayout, 20);
	AssetEditorRect->AddChild(vl_Object_Asset);

	CDisplayText *AssetEditorTExt = new CDisplayText(wsButton);
	AssetEditorTExt->SetText(L"Edit Asset");
	vl_Object_Asset->AddChild(AssetEditorTExt);

	CHorizontal_layout *objectAssetHL = new CHorizontal_layout(wsVerticalLayout,10);
	vl_Object_Asset->AddChild(objectAssetHL);

	CGui2DRect *OpenObject = new CGui2DRect(wsButton);
	objectAssetHL->AddChild(OpenObject);

	CGui2DRect *NewObject = new CGui2DRect(wsButton);
	objectAssetHL->AddChild(NewObject);

	/*
	*	Terrain editor button
	*/
	CVertical_layout *vl_Terrain_Asset = new CVertical_layout(wsVerticalLayout, 20);
	TerrainEditorRect->AddChild(vl_Terrain_Asset);

	CDisplayText *TerrainEditorTExt = new CDisplayText(wsButton);
	TerrainEditorTExt->SetText(L"Edit Asset");
	vl_Terrain_Asset->AddChild(TerrainEditorTExt);

	CHorizontal_layout *TerrainAssetHL = new CHorizontal_layout(wsVerticalLayout, 10);
	vl_Terrain_Asset->AddChild(TerrainAssetHL);

	CGui2DRect *TerrainEditor = new CGui2DRect(wsButton);
	TerrainAssetHL->AddChild(TerrainEditor);

	RegisterGui_ForEvent_Handling(TerrainEditor);
	TerrainEditor->Evenment->Set_OnClick_Callback(std::bind(&CEditorLandScreen::TerrainEditor, this, std::placeholders::_1));
	
	RegisterGui_ForEvent_Handling(NewObject);
	NewObject->Evenment->Set_OnClick_Callback(std::bind(&CEditorLandScreen::New3DAsset, this, std::placeholders::_1));

}


CEditorLandScreen::~CEditorLandScreen()
{
}

void CEditorLandScreen::RunContextLogic(float delta_t)
{
	background->Draw();
}

void CEditorLandScreen::EventProcessing(SDL_Event evt, float delta_t )
{
}

void CEditorLandScreen::New3DAsset(CGui2DRect * caller)
{
	ChangeContext<C3DAssetEditor>(this);
}

void CEditorLandScreen::TerrainEditor(CGui2DRect * caller)
{
	ChangeContext<CTerrainEditor>(this);
}
