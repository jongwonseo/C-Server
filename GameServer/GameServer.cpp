#include "pch.h"
#include <iostream>
#include "CorePch.h"
#include <Windows.h>

mutex m;
queue<int32> q;
HANDLE handle;

// 유저레벨(커널레벨X)(핸들과 차이점)
condition_variable cv;

void Producer()
{
	while (true)
	{
		// 1 락을 잡고
		// 2 공유 변수 값을 수정
		// 3 lock을 풀고
		// 4 조건변수 통해 다른 쓰레드에게 통지

		{
			unique_lock<mutex> lock(m);
			q.push(100);
		}
		
		
		cv.notify_one(); // wait중인 쓰레드 1개 깨움
		//::SetEvent(handle); // signal로 바꿔라
		this_thread::sleep_for(100ms);
	}
}

void Consumer()
{
	
	//// signal상태면 진생, 아니면 잠듬
	//::WaitForSingleObject(handle, INFINITE);
	//
	//// bManualReset True일때 (CreateEvent 속성)
	////::ResetEvent(handle);
	while (true)
	{		
		unique_lock<mutex> lock(m);
		cv.wait(lock, []() {return q.empty() == false; });
		// 1 락을 잡고
		// 2 조건 확인, 만족하면 빠져나가서 이어서 실행
		// 만족하지 않으면 lock을 풀어주고 대기 상태

		
		//while(q.empty() == false)
		{
			int32 data = q.front();
			q.pop();
			cout << q.size() << endl;
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