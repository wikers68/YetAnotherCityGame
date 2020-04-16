#pragma once

/*
*	Base class to draw 2D rectangle with OpenGl Command
*/
#include "GuiBaseRect.h"

#include <functional>
#include <GL/glew.h>
#include <iostream>
#include <SDL.h>

#include "../Option.h"
#include "../Event/Mousse_Event.h"

class CGui2DRect : public CGuiBaseRect
{
public:
	CGui2DRect(std::string argWidth, std::string  argHeight, int argHorizontalPosition, int argVerticalPosition);
	~CGui2DRect();

	GLuint _vertexShader;
	GLuint _pixelShader;

	GLuint _bufferVertex;
	GLuint _vertexArray;

	void DrawLocal(float delta_t = 0.0) override;

	void SetBackGroundColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha = 1.0f);

	//take SDL data about the mousse and search if pointer, is over the Gui or not
	//void Generate_Mousse_Action(SDL_Event evt);

	CMousse_Event<CGui2DRect*> *Evenment;

private:
	
	// background color
	 GLfloat _Red;
	 GLfloat _Green;
	 GLfloat _Blue;
	 GLfloat _Alpha;

	 void CheckMouseClick(SDL_Event evt) override;

	 void CheckMouseIsOver(SDL_Event evt) override;

	 void CheckMouseIsLeaving(SDL_Event evt) override;

};

