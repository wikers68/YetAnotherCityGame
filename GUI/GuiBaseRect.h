#pragma once

/*
*	Base Class to manage rectangular GUI element such as, window, button...
*/

#include <list>
#include <functional>
#include <SDL.h>
#include "../Shaders/Shader.h"

class CGuiBaseRect
{
public:
	CGuiBaseRect();
	CGuiBaseRect(int argWidth,int argHeight, int argHorizontalPosition, int argVerticalPosition );

	~CGuiBaseRect();

	int _Width;
	int _Height;

	int _HorizontalPosition;	//position relative to parent
	int _VerticalPosition;		//position relative to parent

	int _AbsoluteHorizontalPosition;	//absolute position in screen space
	int _AbsoluteVerticalPosition;		//absolute position in screen space

	bool _isVisible;

	CShader *_Shader;	//shader used to draw the BaseRect

	//if something is change (size, parent location...), set to false.
	//bool _ToBeUpdated;

	//update current CGuiBAseRect then children
	void Update(void);

	CGuiBaseRect *_Parent;

	//link to other GuiElement linked to the current CGuiBaseRect 
	std::list<CGuiBaseRect*> *_Child;

	void AddChild(CGuiBaseRect *argChild);

	void Draw(float delta_t = 0.0f);

	//add specific draw instruction of inherited class inside
	virtual void DrawLocal(float delta_t = 0.0f) = 0;

	void DrawChild(void);

	void Hide(void);

	void Show(void);

	bool IsVisible(void);

	/*
	*	True if the pointer was over the element during last frame.
	*	If pointer is not over frame during test, event "OnLeave" is generated
	*/
	bool PointerWasOverLastFrame;

	bool PointerIsInside_Rect(int x, int y);

	void CGuiBaseRect::Generate_Mousse_Action(SDL_Event evt);

	//list of event function
	virtual void CheckMouseClick(SDL_Event evt) = 0;
	virtual void CheckMouseIsOver(SDL_Event evt) = 0;
	virtual void CheckMouseIsLeaving(SDL_Event evt) = 0;

private:

};

