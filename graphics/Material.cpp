#include "stdafx.h"
#include "Material.h"


CMaterial::CMaterial()
{
	baseColorTexture = nullptr;
}


CMaterial::~CMaterial()
{
}

void CMaterial::OpenDialogBoxToImportTexture(TextureType tt)
{
	LPCTSTR FileFilter = L"PNG (*.png) | *.png";

	/*
	*	Create a MFC dialog box
	*/
	CFileDialog fd(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, FileFilter);

	/*
	*	Open and act if a file is selected
	*/
	if (fd.DoModal() == IDOK)
	{
		CString path = fd.GetPathName();

		CString fileExt = fd.GetFileExt();

		std::wcout << "Opening: " << (std::wstring)path << std::endl;

		if (fileExt.Compare(CString("png")) == 0)
		{
			this->baseColorTexture = new CTexture();

			//	https://www.codeproject.com/Tips/175043/Cplusplus-Converting-an-MFC-CString-to-a-std-str-2
			std::string w( CW2A(path.GetString()) );
			baseColorTexture->LoadFromFile(w);
		}
	}
}
