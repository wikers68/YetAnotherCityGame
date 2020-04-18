#include "stdafx.h"
#include "EditorLandScreen.h"


CEditorLandScreen::CEditorLandScreen() : CContext()
{
	background = new CGuiTextureRect(std::to_string(COption::getInstance().Get_Horizontal_Resolution()).append("p")
		, std::to_string(COption::getInstance().Get_Vertical_Resolution()).append("p"), 0, 0);
	CTexture *_textureButton = new CTexture();
	_textureButton->LoadFromFile("../GameRessources/media/GUI/textures/background_menu_1920x1080.png");
	background->SetTexture(_textureButton);

	CVertical_layout *vl = new CVertical_layout("100%", "100%", 0, 0,20);
	background->AddChild(vl);

	CDisplayText *headText = new CDisplayText("100%", "100%", HORIZONTAL_LEFT, 0);
	headText->SetText(L"YetAnotherCityGame... Editor");
	vl->AddChild(headText);

	CHorizontal_layout *hl = new CHorizontal_layout("100%", "100%", 0, 0, 20);
	vl->AddChild(hl);

	CGui2DRect *AssetEditorRect = new CGui2DRect("100%", "100%", 0, 0);
	AssetEditorRect->SetBackGroundColor(34.0 / 255.0, 84.0 / 255.0 , 125.0 / 255.0);
	hl->AddChild(AssetEditorRect);

	CGui2DRect *TerrainEditorRect = new CGui2DRect("100%", "100%", 0, 0);
	hl->AddChild(TerrainEditorRect);
	TerrainEditorRect->SetBackGroundColor(34.0 / 255.0, 84.0 / 255.0, 125.0 / 255.0);

	CGui2DRect *GoBackMainMenu = new CGui2DRect("25%", "100%", 0, 0);
	vl->AddChild(GoBackMainMenu);
	GoBackMainMenu->SetBackGroundColor(0.5, 0.2, 0.5);

	/*
	*	Object editor button
	*/
	CVertical_layout *vl_Object_Asset = new CVertical_layout("100%", "100%", 0, 0, 20);
	AssetEditorRect->AddChild(vl_Object_Asset);

	CDisplayText *AssetEditorTExt = new CDisplayText("100%", "100%", 0, 0);
	AssetEditorTExt->SetText(L"Edit Asset");
	vl_Object_Asset->AddChild(AssetEditorTExt);

	CHorizontal_layout *objectAssetHL = new CHorizontal_layout("100%", "100%", 0, 0,10);
	vl_Object_Asset->AddChild(objectAssetHL);

	CGui2DRect *OpenObject = new CGui2DRect("100%", "100%", 0, 0);
	objectAssetHL->AddChild(OpenObject);

	CGui2DRect *NewObject = new CGui2DRect("100%", "100%", 0, 0);
	objectAssetHL->AddChild(NewObject);

	/*
	*	Terrain editor button
	*/
	CVertical_layout *vl_Terrain_Asset = new CVertical_layout("100%", "100%", 0, 0, 20);
	TerrainEditorRect->AddChild(vl_Terrain_Asset);

	CDisplayText *TerrainEditorTExt = new CDisplayText("100%", "100%", 0, 0);
	TerrainEditorTExt->SetText(L"Edit Asset");
	vl_Terrain_Asset->AddChild(TerrainEditorTExt);

	CHorizontal_layout *TerrainAssetHL = new CHorizontal_layout("100%", "100%", 0, 0, 10);
	vl_Terrain_Asset->AddChild(TerrainAssetHL);

	CGui2DRect *OpenTerrain = new CGui2DRect("100%", "100%", 0, 0);
	TerrainAssetHL->AddChild(OpenTerrain);

	CGui2DRect *NewTerrain = new CGui2DRect("100%", "100%", 0, 0);
	TerrainAssetHL->AddChild(NewTerrain);
	
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
