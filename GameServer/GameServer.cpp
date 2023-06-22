#include "pch.h"
#include <iostream>
#include "CorePch.h"
#include <Windows.h>

mutex m;
queue<int32> q;
HANDLE handle;

void Producer()
{
	while (true)
	{
		{
			unique_lock<mutex> lock(m);
			q.push(100);
		}
		
		::SetEvent(handle); // signal로 바꿔라
		this_thread::sleep_for(100ms);
	}
}

void Consumer()
{
	// signal상태면 진생, 아니면 잠듬
	::WaitForSingleObject(handle, INFINITE);
	
	// bManualReset True일때 (CreateEvent 속성)
	//::ResetEvent(handle);
	while (true)
	{
		unique_lock<mutex> lock(m);
		cout << "consumer" << endl;
		if (q.empty() == false)
		{
			int32 data = q.front();
			q.pop();
			cout << data << endl;
		}
	}
}

int main()
{
	// 커널 오브젝트
	// Usage Count
	// Signal(파란불,true), Non-Signal(빨간불,false)

	handle = ::CreateEvent(NULL/*보안속성*/, FALSE /*자동으로 signal 초기화*/, FALSE, NULL);
	thread t1(Producer);
	thread t2(Consumer);

	t1.join();
	t2.join();

	::CloseHandle(handle);
}