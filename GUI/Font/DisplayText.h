#pragma once

#include <string>
#include <iostream>
#include <algorithm>
#include "../GuiBaseRect.h"
#include "FontManager.h"
#include "../../Option.h"

struct Vertex_Character
{
	float Px;
	float Py;
	float U;
	float V;
};

class CDisplayText :
	public CGuiBaseRect
{
public:
	CDisplayText(Widget_Style style);
	~CDisplayText();

	void SetText(std::wstring text);

	void SetHeight(int Height_Pixel);

	// Inherited via CGuiBaseRect
	virtual void DrawLocal(float delta_t = 0.0f) override;

	virtual bool CheckMouseClick(SDL_Event evt) override { return false; }
	virtual void CheckMouseIsOver(SDL_Event evt) override {};
	virtual void CheckMouseIsLeaving(SDL_Event evt) override {};

	float R;
	float G;
	float B;

	/*
	*	if the calculated width or height of the string is higher than the parent size, we scale the string to max parent size 
	*/
	void AutoScaleText();

	void ActivateAutoScaling(); 
	void ResetAutoScaling();

private:

	int HeightPixel; 

	GLuint _vertexArray;

	//number of character in the string
	int numberOfCharacter;

	/* 
	*	Size of string in pixel.
	*	Calculated during SetText()
	*/
	int StringSize;

	bool AutoScaling;

	float ScaleFactor;
};

