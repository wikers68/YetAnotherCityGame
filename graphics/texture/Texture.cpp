#include "stdafx.h"
#include "Texture.h"

#include <stb_image.h>

CTexture::CTexture()
{
	_glTexture = -1;
}


CTexture::~CTexture()
{
}

GLuint CTexture::LoadFromFile(std::string argFileName)
{
	//data from image, extracted by stb lib
	int imageWidth, imageHeight, chanel;

	//by default we want RGBA texture, even if A chanel is not available in texture
	unsigned char *data = stbi_load(argFileName.c_str(),&imageWidth,&imageHeight,&chanel,STBI_rgb_alpha);

	if (data == nullptr) return -1;

	return CreateTextureFromMemory(imageWidth, imageHeight, 4, data);
}

/*
*	argChanel not use right now. Added if needed in future
*/
GLuint CTexture::CreateTextureFromMemory(int argWidth, int argHeight, int argChanel, void * argData)
{
	glGenTextures(1, &_glTexture);

	glBindTexture(GL_TEXTURE_2D, _glTexture);

	glTextureStorage2D(_glTexture, 1, GL_RGBA8, argWidth, argHeight);
	glTextureSubImage2D(_glTexture, 0, 0, 0, argWidth, argHeight, GL_RGBA, GL_UNSIGNED_BYTE, argData);

	return _glTexture;
}
