#include "pch.h"
#include "UserManager.h"
#include "AccountManager.h"

// accountLock -> userLock ������� �ϸ� �ذ�'

void UserManager::ProcessSave()
{
	// accountLock
	Account* account = AccountManager::Instance()->GetAccount(100);
	
	// userLock
	lock_guard<mutex> guard(_mutex);

	
}