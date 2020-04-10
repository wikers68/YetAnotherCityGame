#include "stdafx.h"
#include "FontManager.h"

CFontManager CFontManager::_singletonInstance = CFontManager();

CFontManager::CFontManager()
{
	CharacterSet = new std::map<int, SCharacter>();

	//resolution of the texture that will pack glyph raster
	TextureResolution = 1024;
	Raster = -1;
}


CFontManager::~CFontManager()
{
}

bool CFontManager::Init_FontManager(void)
{
	/*
	*	First we create an "OpenGL texture" in which we will raster each Glyph
	*/
	glGenTextures(1, &Raster);
	glBindTexture(GL_TEXTURE_2D, Raster);

	/*
	*	image source will have 1byte per pixel (grey level
	*	https://www.freetype.org/freetype2/docs/reference/ft2-basic_types.html#ft_pixel_mode_gray
	*/
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

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

	/*
	*	We check that unicode charmap is available
	*/
	bool UnicodeCharMapFound = false;

	if (face->num_charmaps >= 1)
	{
		for (int n = 0; n < face->num_charmaps; n++)
		{
			int pID = face->charmaps[n]->platform_id;
			int eID = face->charmaps[n]->encoding_id;

			/*
			*	https://tools.ietf.org/doc/libfreetype6/reference/ft2-truetype_tables.html#TT_MS_ID_XXX
			*	pID = 3 ==> platform microsoft
			*	eID = 1 ==> unicode
			*/

			if (pID == 3 && eID ==1 )
			{
				FT_Set_Charmap(face, face->charmaps[n]);
				UnicodeCharMapFound = true;
				break;
			}
		}
	}

	if (UnicodeCharMapFound == false) return false;

	//screen resolution Change by real value?
	int dpi = 76;

	codeErreur = FT_Set_Char_Size(face, 0, pixelHeight * 64, dpi, dpi);

	FT_Long numgyphys = face->num_glyphs;

	int LineNumber = 0;
	int Pixel_Horizontal_offset = 0;

	/*
	* Invert pixel in vertical direction to match OpengGL texture from bottom to top
	*/
	FT_Matrix mirror;
	mirror.xx = (FT_Fixed) 1 * 0x10000L;
	mirror.yy = (FT_Fixed)-1 * 0x10000L;
	mirror.xy = mirror.yx = (FT_Fixed)0;

	FT_Vector translation;
	translation.x = translation.y = 0;

	//we iterate on each glyph to draw them to bitmap
	//for (int g = 0; g < numgyphys; g++)

	FT_UInt characterIndex;
	FT_ULong character;
	character = FT_Get_First_Char(face,&characterIndex);

	while(characterIndex != 0)
	{
		FT_Set_Transform(face, &mirror,&translation );

		codeErreur = FT_Load_Glyph(face, FT_Get_Char_Index(face,character) , FT_LOAD_DEFAULT);
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
		ch.codeCaractere = character;
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

				AddCharacterToSet(ch);
			}
		}

		//next available character from current character
		character = FT_Get_Next_Char(face, character, &characterIndex);
	}

	//restore to default value
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

	return true;
}

void CFontManager::AddCharacterToSet(SCharacter arg)
{
	CharacterSet->insert(std::pair<int, SCharacter>(arg.codeCaractere, arg));
}

SCharacter CFontManager::getCharacter_Code(int code)
{
	
	std::map<int, SCharacter>::iterator results = CharacterSet->find(code);

	if (results != CharacterSet->end())
	{
		/*
		*	The character exist on our base
		*/
		return results->second;
	}
	else
	{
		/*
		*	The character doens't exist on our base.
		*	We return a new character all set to 0.
		*/
		return SCharacter();
	}
}
