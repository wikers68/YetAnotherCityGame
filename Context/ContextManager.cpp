#include "stdafx.h"
#include "ContextManager.h"

CContextManager CContextManager::_singletonInstance = CContextManager();

CContextManager & CContextManager::Instance()
{
	return _singletonInstance;
}

void CContextManager::SetCurrentActiveContext(CContext * _currentActiveContext)
{
	//delete this->_CurrentActiveContext;

	previousContext = _CurrentActiveContext;
	this->_CurrentActiveContext = _currentActiveContext;
}

CContext * CContextManager::GetCurrentActiveContext()
{
	return _CurrentActiveContext;
}

void CContextManager::DeletePreviousContext(void)
{
	if (previousContext != nullptr)
	{
		delete previousContext;
		previousContext = nullptr;
	}	
}

CContextManager::CContextManager()
{
	RunApplication = true;
	previousContext = nullptr;
	_CurrentActiveContext = nullptr;
}


CContextManager::~CContextManager()
{
}
