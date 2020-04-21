#include "stdafx.h"
#include "GuiTextureRect.h"


CGuiTextureRect::CGuiTextureRect(std::string argWidth, std::string  argHeight, int argHorizontalPosition, int argVerticalPosition) :CGuiBaseRect(argWidth, argHeight, argHorizontalPosition, argVerticalPosition)
{
	glGenVertexArrays(1, &_vertexArray);
	glBindVertexArray(_vertexArray);

	float Vertex[12] =
	{
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f
	};

	glGenBuffers(1, &_bufferVertex);	//allocate on free buffer name

	glBindBuffer(GL_ARRAY_BUFFER, _bufferVertex);	//Create the buffer

	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex), &Vertex, GL_STATIC_DRAW);		//fill buffer with data

	//vertex format attribute. Link to the last Buffer "bind command"
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	const char *VertexShaderString =
	{
		"#version 410 core\n"
		"layout( location = 0) in vec2 vertexPosition;"
		"uniform ivec4 PositionSize;"
		"uniform ivec4 ScreenSize;"
		"out vec2 uv;"
		"void main()"
		"{"
		//dimension in viewport space of the rectangle
	"float widthRelToScreen = float(PositionSize.z) / float(ScreenSize.x);"
	"float heightRelToScreen = float(PositionSize.w) / float(ScreenSize.y);"

		//upper left corner position in screen space
	"float Xposition = -1 + 2*(vertexPosition.x * widthRelToScreen + float(PositionSize.x) / float(ScreenSize.x));"
	"float Yposition =  1 - 2*(vertexPosition.y * heightRelToScreen + float(PositionSize.y) / float(ScreenSize.y));"

			"uv = vec2( vertexPosition.x,vertexPosition.y);"
			"gl_Position = vec4( Xposition,Yposition,1,1);"
		"};"
	};

	const char *FragmentShaderString =
	{
		"#version 420 core\n"
		"in vec2 uv;"
		"uniform vec4 Modulation;"
		"layout (location = 0) out vec4 color;"
		"layout (location = 1) out int MaterialID;"
		"uniform sampler2D _Texture;"
		"void main()"
		"{"
		"MaterialID = 255;"
		"color = texture(_Texture,uv)*Modulation;"
		"};"
	};

	_Shader = new CShader();
	_Shader->Compile(VertexShaderString, FragmentShaderString);

	PointerWasOverLastFrame = false;

	Evenment = new CMousse_Event<CGuiTextureRect*>();

	_texture = nullptr;

	glGenSamplers(1, &_Sampler);

	float Modulation_R = Modulation_V = Modulation_B = Modulation_A = 1.0f;
}


CGuiTextureRect::~CGuiTextureRect()
{
}


void CGuiTextureRect::DrawLocal(float delta_t)
{
	if (_texture)
	{
		glUseProgram(_Shader->getShaderProgram());
		glBindVertexArray(_vertexArray);
		glActiveTexture(GL_TEXTURE0);
		glUniform1i(glGetUniformLocation(_Shader->getShaderProgram(), "_Texture"), 0);
		//glBindSampler(0, _Sampler);
		glBindTexture(GL_TEXTURE_2D, this->_texture->getGlTexture());

		glUniform4i(glGetUniformLocation(_Shader->getShaderProgram(), "PositionSize"),
			(GLint)CGuiBaseRect::_AbsoluteHorizontalPosition,
			(GLint)CGuiBaseRect::_AbsoluteVerticalPosition,
			(GLint)CGuiBaseRect::_Width,
			(GLint)CGuiBaseRect::_Height);

		glUniform4i(glGetUniformLocation(_Shader->getShaderProgram(), "ScreenSize"),
			COption::getInstance().Get_Horizontal_Resolution(),
			COption::getInstance().Get_Vertical_Resolution(),
			0,
			0);

		glUniform4f(glGetUniformLocation(_Shader->getShaderProgram(), "Modulation"),
			Modulation_R,
			Modulation_V,
			Modulation_B,
			Modulation_A);

		glDrawArrays(GL_TRIANGLES, 0, 6);
	}

}

void CGuiTextureRect::ModulateColor(float R, float V, float B, float A)
{
	this->Modulation_V = V;
	Modulation_B = B;
	Modulation_R = R;
	Modulation_A = A;
}

void CGuiTextureRect::CheckMouseClick(SDL_Event evt)
{
	if (PointerIsInside_Rect(evt.button.x, evt.button.y) && Evenment->OnClick_CallBackFunction)
	{
		Evenment->OnClick_CallBackFunction(this);
	}
}

void CGuiTextureRect::CheckMouseIsOver(SDL_Event evt)
{
	if (PointerIsInside_Rect(evt.motion.x, evt.motion.y) && Evenment->IsOver_CallBackFunction)
	{
		this->PointerWasOverLastFrame = true;
		  Evenment->IsOver_CallBackFunction(this);
	}
}

void CGuiTextureRect::CheckMouseIsLeaving(SDL_Event evt)
{
	if (Evenment->IsLeaving_CallBackFunction)
	{
		if (PointerWasOverLastFrame && !PointerIsInside_Rect(evt.motion.x, evt.motion.y))
		{
			PointerWasOverLastFrame = false;
			Evenment->IsLeaving_CallBackFunction(this);
		}
	}
}
