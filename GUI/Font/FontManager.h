#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H

#include <GL/glew.h>

struct SCharacter
{
	/*
	*	Horizontal begin and end of character position in texture pack
	*/
	int Horizontal_Start = 0;
	int Horzontal_End = 0;

	int Vertical_Start = 0;
	int Vertical_End = 0;
};

class CFontManager
{
public:

	static CFontManager &getInstance() { return _singletonInstance; };

	bool Init_FontManager(void);

private:
	CFontManager();
	~CFontManager();

	static CFontManager _singletonInstance;

	CFontManager& operator= (const CFontManager&) {}
	CFontManager(const CFontManager&) {}

	FT_Library _ftLibrary;
};

