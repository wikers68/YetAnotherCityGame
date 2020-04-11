#include "stdafx.h"
#include "DisplayText.h"


CDisplayText::CDisplayText(int argWidth, int argHeight, int argHorizontalPosition, int argVerticalPosition) : CGuiBaseRect(argWidth, argHeight, argHorizontalPosition, argVerticalPosition)
{
	const char *VertexShaderString =
	{
		"#version 410 core\n"
		"layout( location = 0) in vec2 vertexPosition;"
		"layout( location = 1) in vec2 vertexUV;"
		"uniform ivec4 PositionSize;"
		"uniform ivec4 ScreenSize;"
		"out vec2 p_uv;"
		"void main()"
		"{"
		//dimension in viewport space of the rectangle
		"float widthRelToScreen = float(PositionSize.z) / float(ScreenSize.x);"
		"float heightRelToScreen = float(PositionSize.w) / float(ScreenSize.y);"

		//upper left corner position in screen space
		"float Xposition = -1 + 2*(vertexPosition.x  + float(PositionSize.x)) / float(ScreenSize.x);"
		"float Yposition =  1 - 2*(vertexPosition.y  + float(PositionSize.y)) / float(ScreenSize.y);"
		" p_uv = vertexUV;"
		"gl_Position = vec4( Xposition,Yposition,1,1);"
		"};"
	};

	const char *FragmentShaderString =
	{
		"#version 420 core\n"
		"in vec2 p_uv;"
		"uniform sampler2D glyph_packed;"
		"uniform vec3 TextColor;"
		"out vec4 color;"
		"void main()"
		"{"

		"if(texture(glyph_packed,p_uv).r <= 0.5f)"
		"{"
		"discard;"
		"}"
		"color = vec4(TextColor,1.0f); "
		"};"
	};

	_Shader = new CShader();
	_Shader->Compile(VertexShaderString, FragmentShaderString);

	HeightPixel = 50;

	//default color is White
	R = G = B = 1.0f;
}


CDisplayText::~CDisplayText()
{
}

void CDisplayText::SetText(std::wstring text)
{
	numberOfCharacter = text.length();

	if (numberOfCharacter > 0)
	{
		/*
		*	We allocate 6 vertex per character (to draw 2 triangles)
		*/
		Vertex_Character *vt = (Vertex_Character*) calloc(6*numberOfCharacter, sizeof(Vertex_Character));

		int offset_Horizontal = 0;

		/*
		*	String is parse character by character
		*/
		for (int c = 0; c < numberOfCharacter; c++)
		{
			/*
			*	as string is a wstring, each character is a UTF16LE.
			*	We use int to get the code... Seems working well !
			*/
			int Windows_Unicode = text[c]; 

			/*
			* for debug purpose only
			*/
			std::cout << Windows_Unicode << std::endl;

			/*
			*	We load glyph data
			*/
			SCharacter ch = CFontManager::getInstance().getCharacter_Code(Windows_Unicode);

			/*
			*	As the packed glyph height size is fixed, we define a scale factor to fix the height wanted by user
			*/
			float Echelle = (float)HeightPixel / (float)CFontManager::getInstance().pixelHeight;
			
			int P0_X = offset_Horizontal;
			int P1_X = 0;

			if (Windows_Unicode == 32)
			{
				/*
				*  Unicode 32 = Space
				*/
				P1_X = offset_Horizontal + (int)(0.5f*(float)HeightPixel);
			}
			else
			{
				P1_X = offset_Horizontal + (int)((float)(ch.Horzontal_End - ch.Horizontal_Start)*Echelle);
			}
			int Y = (int)((float)(ch.Vertical_End - ch.Vertical_Start) * Echelle); // HeightPixel;

			//TODO: add centerline management to not align all character on same line...

			Vertex_Character v0;
			v0.Px = P0_X;
			v0.Py = HeightPixel - Y;
			v0.U = (float)ch.Horizontal_Start / (float)CFontManager::getInstance().getTexture_Resolution();
			v0.V = 1-(float)ch.Vertical_Start / (float)CFontManager::getInstance().getTexture_Resolution();
			
			Vertex_Character v1;
			v1.Px = P1_X;
			v1.Py = HeightPixel - Y;
			v1.U = (float)ch.Horzontal_End / (float)CFontManager::getInstance().getTexture_Resolution();
			v1.V = v0.V;

			Vertex_Character v2;
			v2.Px = P1_X;
			v2.Py = HeightPixel;
			v2.U = v1.U;
			v2.V = 1-(float)ch.Vertical_End / (float)CFontManager::getInstance().getTexture_Resolution();

			Vertex_Character v3;
			v3.Px = P0_X;
			v3.Py = HeightPixel;
			v3.U = v0.U;
			v3.V = v2.V;

			vt[(c * 6)] = v0;
			vt[(c * 6)+1] = v1;
			vt[(c * 6)+2] = v2;

			vt[(c * 6)+3] = v2;
			vt[(c * 6)+4] = v0;
			vt[(c * 6)+5] = v3;

			offset_Horizontal = P1_X;
		}

		if (vt)
		{
			glGenVertexArrays(1, &_vertexArray);
			glBindVertexArray(_vertexArray);

			GLuint vertexBuffer;
			glGenBuffers(1, &vertexBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

			/*
			*	Comment : buffer size to copy = total size of element in byte
			*/
			glBufferData(GL_ARRAY_BUFFER,6*numberOfCharacter*sizeof(Vertex_Character), vt, GL_STATIC_DRAW);

			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex_Character), (void*) 0);
			glEnableVertexAttribArray(0);

			glVertexAttribPointer(1, 2, GL_FLOAT, GL_TRUE, sizeof(Vertex_Character), (void*)offsetof(Vertex_Character,U));
			glEnableVertexAttribArray(1);
		}

		StringSize = offset_Horizontal;
		free(vt);
	}
}

void CDisplayText::SetHeight(int Height_Pixel)
{
	this->HeightPixel = Height_Pixel;
}

void CDisplayText::DrawLocal(float delta_t)
{
	glUseProgram(_Shader->getShaderProgram());
	glBindVertexArray(_vertexArray);

	glUniform4i(glGetUniformLocation(_Shader->getShaderProgram(), "PositionSize"),
		(GLint)_AbsoluteHorizontalPosition,
		(GLint)_AbsoluteVerticalPosition,
		(GLint)_Width,
		(GLint)_Height);

	glUniform4i(glGetUniformLocation(_Shader->getShaderProgram(), "ScreenSize"),
		COption::getInstance().Get_Horizontal_Resolution(),
		COption::getInstance().Get_Vertical_Resolution(),
		0,
		0);

	glUniform3f(glGetUniformLocation(_Shader->getShaderProgram(), "TextColor"),
		R,
		G,
		B);

	/*
	*	We bind the texture with all glyphs 
	*/
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, CFontManager::getInstance().getPackedGlyphRaster());

	/*
	*	There are 6 vertices per character
	*/
	glDrawArrays(GL_TRIANGLES, 0, numberOfCharacter * 6);
}
