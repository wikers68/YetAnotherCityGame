#pragma once

/*
*	Base Class to manage rectangular GUI element such as, window, button...
*/

#include <list>
#include <functional>
#include <string>
#include <SDL.h>
#include "../Shaders/Shader.h"

#define HORIZONTAL_CENTER -1
#define HORIZONTAL_LEFT -2
#define HORIZONTAL_RIGHT -3

enum Translate_Size
{
	WIDTH,
	HEIGHT,
};


class CGuiBaseRect
{
public:
	CGuiBaseRect();
	CGuiBaseRect(std::string argWidth, std::string  argHeight, int argHorizontalPosition, int argVerticalPosition );

	~CGuiBaseRect();

	std::string commandWidthString;
	std::string commandHeightString;

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

	void CGuiBaseRect::Generate_Mousse_Action(SDL_Event evt);

	//list of event function
	virtual void CheckMouseClick(SDL_Event evt) = 0;
	virtual void CheckMouseIsOver(SDL_Event evt) = 0;
	virtual void CheckMouseIsLeaving(SDL_Event evt) = 0;

	int getHeight(void);
	int getWidth(void);

	void Reset_HasBeenCalculated(void);

	void SetCommandString(std::string command, Translate_Size ts);

private:

	/*
	*	use to translate arg in string format to size:
	*		- string ended by p ==> size is in pixel
	*		- string ended by % ==> size is in parent size %
	*/
	int TranslateStringToSize(std::string arg, Translate_Size ts);

	/*
	*	True if size argument (in string format) has been translated into int type (pixel size)
	*/
	bool SizeHasBeenCalculated;

	void CalculateSize(void);

};

