#pragma once

#include "Context.h"

class CContextManager
{
public:
	static CContextManager &Instance();

	void SetCurrentActiveContext(CContext *_currentActiveContext);
	CContext *GetCurrentActiveContext();

	bool getRunApplication(void) { return RunApplication; }
	void stopApplication(void) { RunApplication = false; }

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

