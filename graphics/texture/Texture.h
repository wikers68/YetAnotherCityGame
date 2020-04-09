#pragma once

#include <string>
#include <GL/glew.h>

class CTexture
{
public:
	CTexture();
	~CTexture();

	GLuint LoadFromFile(std::string argFileName);

	GLuint getGlTexture(void) { return _glTexture; }

	GLuint CreateTextureFromMemory(int argWidth, int argHeight, int argChanel, void *argData);

private:
	GLuint _glTexture;
};

