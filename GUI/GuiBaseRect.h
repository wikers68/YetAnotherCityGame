#pragma once

/*
*	Base Class to manage rectangular GUI element such as, window, button...
*/

#include <list>
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

	CShader *_Shader;	//shader used to draw the BaseRect

	//if something is change (size, parent location...), set to false.
	//bool _ToBeUpdated;

	//update current CGuiBAseRect then children
	void Update(void);

	CGuiBaseRect *_Parent;

	//link to other GuiElement linked to the current CGuiBaseRect 
	std::list<CGuiBaseRect*> *_Child;

	void AddChild(CGuiBaseRect *argChild);

	virtual void Draw(void) {};

private:

};

