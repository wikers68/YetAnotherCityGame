#pragma once

#include "Context.h"

/*
*	Added to solve cyclic header file dependency 
*/
class CContext;

class CContextManager
{
public:
	static CContextManager &Instance();

	void SetCurrentActiveContext(CContext *_currentActiveContext);
	CContext *GetCurrentActiveContext();
	CContext *previousContext;

	bool getRunApplication(void) { return RunApplication; }
	void stopApplication(void) { RunApplication = false; }

	void DeletePreviousContext(void);

private:
	static CContextManager _singletonInstance;

	CContextManager();
	~CContextManager();

	CContextManager& operator= (const CContextManager&) {}
	CContextManager(const CContextManager&) {}

	CContext *_CurrentActiveContext = nullptr;

	//used to run or to exit applicaton; 
	bool RunApplication;
};