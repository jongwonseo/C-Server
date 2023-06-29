#include "pch.h"
#include <iostream>
#include "CorePch.h"
#include <atomic>
#include <mutex>
#include <windows.h>
#include <future>
#include "ThreadManager.h"

#include "socketUtils.h"

int main()
{
	SOCKET socket = SocketUtils::CreateSocket();

	SocketUtils::BindAnyAddress(socket, 7777);
	SocketUtils::Listen(socket);

	::accept(socket, nullptr, nullptr);

	GThreadManager->Join();
}