#pragma once

/*
*	Base class to manage game option as resoltion, full screen, ...
*	Use singleton patern to be accessible every where
*/

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class COption
{
public:
	static COption &getInstance();

	//read option from hard drive
	bool Read_Option();

	void Set_Horizontal_Resolution(int arg);
	int Get_Horizontal_Resolution(void);

	void Set_Vertical_Resolution(int arg);
	int Get_Vertical_Resolution(void);

	glm::mat4 getMatriceProjection(void);

private:
	static COption _Instance;

	COption();
	~COption();

	COption& operator= (const COption&) {}
	COption(const COption&) {}

	int _Horizontal_Resolution;
	int _Vertical_Resolution;

	bool ProjectionMatriceIsUpToDate;
	glm::mat4 matriceProjection;
};

