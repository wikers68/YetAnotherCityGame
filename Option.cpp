#include "stdafx.h"
#include "Option.h"

COption COption::_Instance = COption();

COption & COption::getInstance()
{
	return _Instance;
}

bool COption::Read_Option()
{
	//read option from file

	Set_Horizontal_Resolution(1280);
	Set_Vertical_Resolution(760);

	ProjectionMatriceIsUpToDate = false;

	return false;
}

void COption::Set_Horizontal_Resolution(int arg)
{
	_Horizontal_Resolution = arg;
}

int COption::Get_Horizontal_Resolution(void)
{
	return _Horizontal_Resolution;
}

void COption::Set_Vertical_Resolution(int arg)
{
	_Vertical_Resolution = arg;
}

int COption::Get_Vertical_Resolution(void)
{
	return _Vertical_Resolution;
}

glm::mat4 COption::getMatriceProjection(void)
{
	if (ProjectionMatriceIsUpToDate)
	{
		return matriceProjection;
	}
	else
	{
		matriceProjection = glm::perspectiveFovRH(glm::radians(45.0f),
			(float)Get_Horizontal_Resolution(),
			(float)Get_Vertical_Resolution(),
			0.1f,
			100.0f);

		ProjectionMatriceIsUpToDate = true;

		return matriceProjection;
	}
}

float COption::getCamera_TranslationSpeed(void)
{
	return 1.0f;
}

float COption::getCamera_RotationSpeed(void)
{
	return 5.0f;
}

COption::COption()
{
	ProjectionMatriceIsUpToDate = false;
}


COption::~COption()
{
}
