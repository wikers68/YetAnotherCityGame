#pragma once

#include <afxdlgs.h>
#include <afxpriv.h>
#include <iostream>
#include <string>

#include "texture\Texture.h"

enum TextureType
{
	BASE_COLOR,
};

class CMaterial
{
public:
	CMaterial();
	~CMaterial();

	CTexture *baseColorTexture;

	void OpenDialogBoxToImportTexture(TextureType tt);
};

