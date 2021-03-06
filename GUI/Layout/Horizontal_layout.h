#pragma once
#include "../GuiBaseRect.h"
#include "EmptySlot.h"

class CHorizontal_layout : 	public CGuiBaseRect
{
public:
	CHorizontal_layout(Widget_Style style,	int spaceBetweenChild = 0);
	~CHorizontal_layout();

	//void SetSpaceBetweenChild(int space);

	// Inherited via CGuiBaseRect

	/*
	*	Vertical layout will not draw something specific
	*/
	virtual void DrawLocal(float delta_t = 0.0f) override {};

	/*
	*	It's not plan to manage event for layout
	*/
	virtual bool CheckMouseClick(SDL_Event evt) override { return false; }
	virtual void CheckMouseIsOver(SDL_Event evt) override {};
	virtual void CheckMouseIsLeaving(SDL_Event evt) override {};
	
	/*
	*	Override parent function to execute an update function when a child is added
	*/
	void AddChild(CGuiBaseRect *argChild) override;

	/*
	*	Specific update function to set children size
	*/

	virtual void Update(void) override;

private:
	int Space;
};

