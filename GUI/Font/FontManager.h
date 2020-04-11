#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H

#include <GL/glew.h>
#include <map>

struct SCharacter
{
	/*
	*	Horizontal begin and end of character position in texture pack
	*/
	int Horizontal_Start = 0;
	int Horzontal_End = 0;

	int Vertical_Start = 0;
	int Vertical_End = 0;

	unsigned long codeCaractere = 0;
};

class CFontManager
{
public:

	static CFontManager &getInstance() { return _singletonInstance; };

	bool Init_FontManager(void);

	void AddCharacterToSet(SCharacter arg);

	SCharacter getCharacter_Code(int code);

	int getTexture_Resolution(void) { return TextureResolution; };

	GLuint getPackedGlyphRaster(void) { return Raster; }

	/*
	*	Max size of the character to draw in bitmap
	*/
	const int pixelHeight = 72;

	/*
	*	We define a number to have a dead spac between two characters
	*/
	const int PixelGap = 6;

private:
	CFontManager();
	~CFontManager();

	static CFontManager _singletonInstance;

	CFontManager& operator= (const CFontManager&) {}
	CFontManager(const CFontManager&) {}

	FT_Library _ftLibrary;

	std::map<int, SCharacter> *CharacterSet;

	//resolution of the texture that will pack glyph raster
	int TextureResolution;

	/*
	*	Packed texture of glyphs
	*/
	GLuint Raster;
};

