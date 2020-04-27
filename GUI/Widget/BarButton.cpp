#include "stdafx.h"
#include "BarButton.h"


CBarButton::CBarButton(int BarHeight):CGuiBaseRect()
{
	/*
	*	Set the bar size
	*/
	Widget_Style barStyle;
	barStyle.hPosition = HORIZONTAL_LEFT;
	barStyle.vPosition = VERTICAL_TOP;
	barStyle.hSize.size = 100;
	barStyle.hSize.AbsOrRel = ABS_REL::_RELATIVE;
	barStyle.hSize.relTo = SIZE_RELATIVE_TO::PARENT;
	barStyle.vSize.size = BarHeight;
	barStyle.vSize.AbsOrRel = ABS_REL::_ABSOLUTE;
	
	this->style = barStyle;

	/*
	*	Add a color background
	*/
	Widget_Style wsTopMenuBackGround;
	wsTopMenuBackGround.hPosition = HORIZONTAL_LEFT;
	wsTopMenuBackGround.vPosition = VERTICAL_TOP;
	wsTopMenuBackGround.hSize.size = 100;
	wsTopMenuBackGround.hSize.AbsOrRel = ABS_REL::_RELATIVE;
	wsTopMenuBackGround.hSize.relTo = SIZE_RELATIVE_TO::PARENT;
	wsTopMenuBackGround.vSize.size = 100;
	wsTopMenuBackGround.vSize.AbsOrRel = ABS_REL::_RELATIVE;
	wsTopMenuBackGround.vSize.relTo = SIZE_RELATIVE_TO::PARENT;

	TopMenuBackGround = new CGui2DRect(wsTopMenuBackGround);

	/*
	*	Add an horizontal layout
	*/
	Widget_Style wsTopMenu_Layout;
	wsTopMenu_Layout.hPosition = 0;
	wsTopMenu_Layout.vPosition = 0;
	wsTopMenu_Layout.hSize.size = 100;
	wsTopMenu_Layout.hSize.AbsOrRel = ABS_REL::_RELATIVE;
	wsTopMenu_Layout.hSize.relTo = SIZE_RELATIVE_TO::PARENT;
	wsTopMenu_Layout.vSize.size = 100;
	wsTopMenu_Layout.vSize.AbsOrRel = ABS_REL::_RELATIVE;
	wsTopMenu_Layout.vSize.relTo = SIZE_RELATIVE_TO::PARENT;

	hl = new CHorizontal_layout(wsTopMenu_Layout, 10);
	
	this->AddChild(TopMenuBackGround);

	TopMenuBackGround->AddChild(hl);
}


CBarButton::~CBarButton()
{
}

void CBarButton::DrawLocal(float delta_t)
{
	TopMenuBackGround->Draw();
}

bool CBarButton::CheckMouseClick(SDL_Event evt)
{
	return false;
}

void CBarButton::CheckMouseIsOver(SDL_Event evt)
{
}

void CBarButton::CheckMouseIsLeaving(SDL_Event evt)
{
}

CGui2DRect * CBarButton::AddTextualButton(std::wstring buttonTExt)
{
	Widget_Style wsButton;
	wsButton.hPosition = HORIZONTAL_CENTER;
	wsButton.vPosition = VERTICAL_CENTER; //TODO: bug, n'aligne pas le widget au milieu du parent
	wsButton.hSize.size = 100;
	wsButton.hSize.AbsOrRel = ABS_REL::_RELATIVE;
	wsButton.hSize.relTo = SIZE_RELATIVE_TO::PARENT;
	wsButton.vSize.size = 80;
	wsButton.vSize.AbsOrRel = ABS_REL::_RELATIVE;
	wsButton.vSize.relTo = SIZE_RELATIVE_TO::PARENT;

	CGui2DRect *Button = new CGui2DRect(wsButton);
	Button->SetBackGroundColor(BUTTON_BACKGROUND_OVER_COLOR);

	hl->AddChild(Button);

	Widget_Style wsTitre;
	wsTitre.hPosition = HORIZONTAL_CENTER;
	wsTitre.vPosition = VERTICAL_CENTER;
	wsTitre.vSize.size = 100;
	wsTitre.vSize.AbsOrRel = ABS_REL::_RELATIVE;;
	wsTitre.vSize.relTo = SIZE_RELATIVE_TO::PARENT;
	wsTitre.hSize.size = 100;
	wsTitre.hSize.AbsOrRel = ABS_REL::_RELATIVE;
	wsTitre.hSize.relTo = SIZE_RELATIVE_TO::PARENT;

	CDisplayText *AssetType = new CDisplayText(wsTitre);
	AssetType->SetText(buttonTExt);
	//AssetType->AutoScaleText();
	Button->AddChild(AssetType);

	return Button;
}

