#include "pch.h"
#include "AccountManager.h"
#include "UserManager.h"

// accountLock -> userLock 순서대로 하면 해결'

void AccountManager::ProcessLogin()
{
	// accountLock
	lock_guard<mutex> guard(_mutex);

	// userLock
	User* user = UserManager::Instance()->GetUser(100);

}