#include "pch.h"
#include "UserManager.h"
#include "AccountManager.h"

// accountLock -> userLock 순서대로 하면 해결'

void UserManager::ProcessSave()
{
	// accountLock
	Account* account = AccountManager::Instance()->GetAccount(100);
	
	// userLock
	lock_guard<mutex> guard(_mutex);

	
}