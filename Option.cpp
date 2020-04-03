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

COption::COption()
{
}


COption::~COption()
{
}
