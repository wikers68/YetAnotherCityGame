#pragma once

/*
*	Base Class to manage rectangular GUI element such as, window, button...
*/

#include <list>
#include <functional>
#include <string>
#include <SDL.h>
#include "../Shaders/Shader.h"
#include "../Option.h"

#define HORIZONTAL_CENTER -1
#define HORIZONTAL_LEFT -2
#define HORIZONTAL_RIGHT -3
#define VERTICAL_CENTER -1
#define VERTICAL_TOP -2
#define VERTICAL_BOTTOM -3

enum Translate_Size
{
	WIDTH,
	HEIGHT,
};

enum SIZE_RELATIVE_TO
{
	NONE,
	PARENT,
	CHILDREN,
};

enum ABS_REL
{
	_ABSOLUTE,
	_RELATIVE,
};

struct WidgetSize
{
	//smallest size of widget, in pixel
	int min = 0;

	// wider size of the widget. -1 = no size limit
	int max = -1;

	// define if size is in pixel (absolute) or in percentage (relative)
	ABS_REL AbsOrRel = ABS_REL::_ABSOLUTE;

	//if size is relative, to parent or children ? 
	SIZE_RELATIVE_TO relTo;

	/*
	*	
	*/
	float size = 0;
};

struct Widget_Style
{

	/*
	*	Where do we place the widget in screen space
	*	Always relative to parent position
	*/
	int hPosition = 0; 
	int vPosition = 0;

	//widget width
	WidgetSize hSize;

	//widget height
	WidgetSize vSize;
};

class CGuiBaseRect
{
public:
	CGuiBaseRect();
	CGuiBaseRect(Widget_Style style );

	~CGuiBaseRect();

	Widget_Style style;

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
	virtual void Update(void);

	CGuiBaseRect *_Parent;

	//link to other GuiElement linked to the current CGuiBaseRect 
	std::list<CGuiBaseRect*> *_Child;

	virtual void AddChild(CGuiBaseRect *argChild);

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

	//list of event function
	virtual bool CheckMouseClick(SDL_Event evt) = 0;
	virtual void CheckMouseIsOver(SDL_Event evt) = 0;
	virtual void CheckMouseIsLeaving(SDL_Event evt) = 0;

	int getHeight(void);
	int getWidth(void);

	void Reset_HasBeenCalculated(void);

private:

	/*
	*	True if size argument (in string format) has been translated into int type (pixel size)
	*/
	bool SizeHasBeenCalculated;

	void CalculateSize(void);

	void Calc_PositionNoParent(void);
	void Calc_PositionWithParent(void);

};

