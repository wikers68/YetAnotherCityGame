#pragma once

#include <functional>

template <class C>
class CMousse_Event
{
public:
	CMousse_Event() 
	{
		Parent = nullptr;
	};

	~CMousse_Event() {};

	C Parent; //class using this CMousse_Event Class

	 /*
	 *	Solution to "easy callback function" from https://stackoverflow.com/questions/14189440/c-callback-using-class-member
	*/
	void Set_OnClick_Callback(std::function<void(C)> func) { OnClick_CallBackFunction = func; };
	std::function<void(C)> OnClick_CallBackFunction;

	//Change background Color if pointer is over
	void Set_IsOver_Callback(std::function<void(C)> func) { IsOver_CallBackFunction = func; }
	std::function<void(C)> IsOver_CallBackFunction;

	//Change background Color if pointer is Leaving the Element
	void Set_IsLeaving_Callback(std::function<void(C)> func) { IsLeaving_CallBackFunction = func; };
	std::function<void(C)> IsLeaving_CallBackFunction;
};

