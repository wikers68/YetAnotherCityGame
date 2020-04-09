#include "stdafx.h"
#include "FontManager.h"

CFontManager CFontManager::_singletonInstance = CFontManager();

CFontManager::CFontManager()
{

}


CFontManager::~CFontManager()
{
}

bool CFontManager::Init_FontManager(void)
{
	/*
	*	First we create an "OpenGL texture" in which we will raster each Glyph
	*/
	//glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	GLuint Raster;
	glGenTextures(1, &Raster);
	glBindTexture(GL_TEXTURE_2D, Raster);


	//resolution of the texture that will pack glyph raster
	int TextureResolution = 2048;


	/*
	*	define one texture only with one color
	*/
	glTextureStorage2D(Raster, 1, GL_R8, TextureResolution, TextureResolution);


	/*
	*	Set all pixel to 0 (black)
	*/
	unsigned char *clear = (unsigned char*)calloc(TextureResolution*TextureResolution, sizeof(unsigned char));
	glTextureSubImage2D(Raster, 0, 0, 0, TextureResolution, TextureResolution, GL_RED, GL_UNSIGNED_BYTE, clear);

	/*
	*	Following instruction are based on https://www.freetype.org/freetype2/docs/tutorial/step1.html
	*/

	FT_Error codeErreur;
	codeErreur = FT_Init_FreeType(&_ftLibrary);

	if (codeErreur)
	{
		return false;
	}

	FT_Face face;

	codeErreur = FT_New_Face(_ftLibrary, "../GameRessources/font/TechnaSansRegular/TechnaSansRegular-Xp79.otf", 0, &face);

	if (codeErreur == FT_Err_Unknown_File_Format)
	{
		return false;
	}
	else if (codeErreur)
	{
		return false;
	}

	//screen resolution Change by real value?
	int dpi = 76;
	int pixelHeight = 64;

	codeErreur = FT_Set_Char_Size(face, 0, pixelHeight * 64, dpi, dpi);

	FT_Long numgyphys = face->num_glyphs;

	int LineNumber = 0;
	int Pixel_Horizontal_offset = 0;

	//we iterate on each glyph to draw them to bitmap
	for (int g = 0; g < numgyphys; g++)
	{
		codeErreur = FT_Load_Glyph(face, g, FT_LOAD_DEFAULT);
		codeErreur = FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL);
	
		int bitmapRes_With = face->glyph->bitmap.width;
		int bitmapRes_Height = face->glyph->bitmap.rows;

		/*
		*	Check that for active Column, the glyph will "enter" in the texture.
		*	If it's not the case, we go to next texture line and first column
		*/
		if (Pixel_Horizontal_offset + bitmapRes_With >= TextureResolution)
		{
			Pixel_Horizontal_offset = 0;
			LineNumber += 1;
		}

		SCharacter ch;
		ch.Horizontal_Start = Pixel_Horizontal_offset;
		ch.Vertical_Start = LineNumber*pixelHeight;
		ch.Vertical_End = ch.Vertical_Start + bitmapRes_Height;
		Pixel_Horizontal_offset += bitmapRes_With;

		ch.Horzontal_End = Pixel_Horizontal_offset;

		/*
		*	draw the glyph bitmap in the Texture raster
		*/
		if (face->glyph->bitmap.buffer != nullptr)
		{

			if (face->glyph->bitmap.pixel_mode == FT_PIXEL_MODE_GRAY )
			{
				glTexSubImage2D(GL_TEXTURE_2D,
					0,
					ch.Horizontal_Start,
					TextureResolution-ch.Vertical_End,
					(ch.Horzontal_End - ch.Horizontal_Start),
					ch.Vertical_End - ch.Vertical_Start,
					GL_RED, GL_UNSIGNED_BYTE,
					face->glyph->bitmap.buffer);

			}
		}
	}

	return true;
}