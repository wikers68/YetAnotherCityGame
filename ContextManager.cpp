#include "stdafx.h"
#include "ContextManager.h"

CContextManager CContextManager::_singletonInstance = CContextManager();

CContextManager & CContextManager::Instance()
{
	return _singletonInstance;
}

void CContextManager::SetCurrentActiveContext(CContext * _currentActiveContext)
{
	this->_CurrentActiveContext = _currentActiveContext;
}

CContext * CContextManager::GetCurrentActiveContext()
{
	return _CurrentActiveContext;
}

CContextManager::CContextManager()
{
}


CContextManager::~CContextManager()
{
}
