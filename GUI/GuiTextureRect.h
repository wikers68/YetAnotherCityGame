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
#include "../graphics/texture/Texture.h"

class CGuiTextureRect : public CGuiBaseRect
{
public:
	CGuiTextureRect(Widget_Style style);
	~CGuiTextureRect();

	GLuint _vertexShader;
	GLuint _pixelShader;

	GLuint _bufferVertex;
	GLuint _vertexArray;

	GLuint _Sampler;

	void DrawLocal(float delta_t = 0.0) override;

	void SetTexture(CTexture *texture) { this->_texture = texture; }

	CMousse_Event<CGuiTextureRect*> *Evenment;

	void ModulateColor(float R, float V, float B, float A = 1.0f);

private:
	
	CTexture *_texture;

	 void CheckMouseClick(SDL_Event evt) override;

	 void CheckMouseIsOver(SDL_Event evt) override;

	 void CheckMouseIsLeaving(SDL_Event evt) override;

	 float Modulation_R;
	 float Modulation_V;
	 float Modulation_B;
	 float Modulation_A;
};

