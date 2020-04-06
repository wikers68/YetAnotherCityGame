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

class CGui2DRect : public CGuiBaseRect
{
public:
	CGui2DRect(int argWidth, int argHeight, int argHorizontalPosition, int argVerticalPosition);
	~CGui2DRect();

	GLuint _vertexShader;
	GLuint _pixelShader;

	GLuint _bufferVertex;
	GLuint _vertexArray;

	void Draw(void) override;

	void SetBackGroundColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha = 1.0f);

	void Hide(void);

	void Show(void);

	bool IsVisible(void);

	//take SDL data about the mousse and search if pointer, is over the Gui or not
	void Generate_Mousse_Action(SDL_Event evt);

	/*
	*	Solution to "easy callback function" from https://stackoverflow.com/questions/14189440/c-callback-using-class-member
	*/
	void Set_OnClick_Callback(std::function<void(CGui2DRect*)> func);
	std::function<void(CGui2DRect*)> OnClick_CallBackFunction;

	//Change background Color if pointer is over
	void Set_IsOver_Callback(std::function<void(CGui2DRect*)> func);
	std::function<void(CGui2DRect*)> IsOver_CallBackFunction;

	//Change background Color if pointer is Leaving the Element
	void Set_IsLeaving_Callback(std::function<void(CGui2DRect*)> func);
	std::function<void(CGui2DRect*)> IsLeaving_CallBackFunction;

private:
	
	// background color
	 GLfloat _Red;
	 GLfloat _Green;
	 GLfloat _Blue;
	 GLfloat _Alpha;

	 bool _isVisible;

	 void DrawChild(void);

	 void CheckMouseClick(SDL_Event evt);

	 void CheckMouseIsOver(SDL_Event evt);

	 void CheckMouseIsLeaving(SDL_Event evt);

	 bool PointerIsInside_Rect(int x, int y);

	 /*
	 *	True if the pointer was over the element during last frame.
	 *	If pointer is not over frame during test, event "OnLeave" is generated
	 */
	 bool PointerWasOverLastFrame;
};

