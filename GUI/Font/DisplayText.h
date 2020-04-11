#pragma once

#include <string>
#include <iostream>
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
	CDisplayText(int argWidth, int argHeight, int argHorizontalPosition, int argVerticalPosition);
	~CDisplayText();

	void SetText(std::wstring text);

	void SetHeight(int Height_Pixel);

	// Inherited via CGuiBaseRect
	virtual void DrawLocal(float delta_t = 0.0f) override;

	virtual void CheckMouseClick(SDL_Event evt) override {};
	virtual void CheckMouseIsOver(SDL_Event evt) override {};
	virtual void CheckMouseIsLeaving(SDL_Event evt) override {};

	float R;
	float G;
	float B;

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
};

