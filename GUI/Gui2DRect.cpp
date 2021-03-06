#include "stdafx.h"
#include "Gui2DRect.h"


CGui2DRect::CGui2DRect(Widget_Style style) :CGuiBaseRect(style), CEventTarget()
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
		"uniform vec4 BackGroundColor;"
		"out vec4 ColorRG;"
		"void main()"
		"{"
			//dimension in viewport space of the rectangle
		"float widthRelToScreen = float(PositionSize.z) / float(ScreenSize.x);"
		"float heightRelToScreen = float(PositionSize.w) / float(ScreenSize.y);"

			//upper left corner position in screen space
		"float Xposition = -1 + 2*(vertexPosition.x * widthRelToScreen + float(PositionSize.x) / float(ScreenSize.x));"
		"float Yposition =  1 - 2*(vertexPosition.y * heightRelToScreen + float(PositionSize.y) / float(ScreenSize.y));"

		"ColorRG = vec4(BackGroundColor.x,BackGroundColor.y,BackGroundColor.z,1.0f);"
		"gl_Position = vec4( Xposition,Yposition,1,1);"

		"};"
	};

	const char *FragmentShaderString =
	{
		"#version 420 core\n"
		"in vec4 ColorRG;"
		"uniform int ID;"
		"layout (location = 1) out vec4 color;"
		"layout (location = 2) out int MaterialID;"
		"layout (location = 3) out int Object_ID;"
		"void main()"
		"{"
		"Object_ID = ID;"
		"MaterialID=255;"
		"color = vec4(ColorRG.x,ColorRG.y,ColorRG.z,1.0f);"
		"};"
	};

	_Shader = new CShader();
	_Shader->Compile(VertexShaderString, FragmentShaderString);

	//set default color
	SetBackGroundColor(0.5f, 0.5f, 0.5f);

	PointerWasOverLastFrame = false;

	Evenment = new CMousse_Event<CGui2DRect*>();
}


CGui2DRect::~CGui2DRect()
{
	if (_Child) _Child->clear();
	delete _Child;
}

void CGui2DRect::SetBackGroundColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
	this->_Red = red;
	this->_Green = green;
	this->_Blue = blue;
	this->_Alpha = alpha;
}

void CGui2DRect::DrawLocal(float delta_t)
{
		glUseProgram(_Shader->getShaderProgram());
		glBindVertexArray(_vertexArray);

		glUniform4i(glGetUniformLocation(_Shader->getShaderProgram(), "PositionSize"),
			(GLint)_AbsoluteHorizontalPosition,
			(GLint)_AbsoluteVerticalPosition,
			(GLint)getWidth()/*_Width*/,
			(GLint)getHeight()/*_Height*/);

		glUniform4i(glGetUniformLocation(_Shader->getShaderProgram(), "ScreenSize"),
			COption::getInstance().Get_Horizontal_Resolution(),
			COption::getInstance().Get_Vertical_Resolution(),
			0,
			0);

		glUniform1i(glGetUniformLocation(_Shader->getShaderProgram(), "ID"), this->getId());

		glUniform4f(glGetUniformLocation(_Shader->getShaderProgram(), "BackGroundColor"),
			_Red,
			_Green,
			_Blue,
			_Alpha);

		glDrawArrays(GL_TRIANGLES, 0, 6);

}

bool CGui2DRect::CheckMouseClick(SDL_Event evt)
{
	Evenment->OnClick_CallBackFunction(this);

	return false;
}

void CGui2DRect::CheckMouseIsOver(SDL_Event evt)
{
	if (PointerIsInside_Rect(evt.motion.x, evt.motion.y) && Evenment->IsOver_CallBackFunction)
	{
		this->PointerWasOverLastFrame = true;
		  Evenment->IsOver_CallBackFunction(this);
	}
}

void CGui2DRect::CheckMouseIsLeaving(SDL_Event evt)
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
