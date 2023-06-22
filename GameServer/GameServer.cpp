#include "pch.h"
#include <iostream>
#include "CorePch.h"
#include <Windows.h>

mutex m;
queue<int32> q;
HANDLE handle;

// ��������(Ŀ�η���X)(�ڵ�� ������)
condition_variable cv;

void Producer()
{
	while (true)
	{
		// 1 ���� ���
		// 2 ���� ���� ���� ����
		// 3 lock�� Ǯ��
		// 4 ���Ǻ��� ���� �ٸ� �����忡�� ����

		{
			unique_lock<mutex> lock(m);
			q.push(100);
		}
		
		
		cv.notify_one(); // wait���� ������ 1�� ����
		//::SetEvent(handle); // signal�� �ٲ��
		this_thread::sleep_for(100ms);
	}
}

void Consumer()
{
	
	//// signal���¸� ����, �ƴϸ� ���
	//::WaitForSingleObject(handle, INFINITE);
	//
	//// bManualReset True�϶� (CreateEvent �Ӽ�)
	////::ResetEvent(handle);
	while (true)
	{		
		unique_lock<mutex> lock(m);
		cv.wait(lock, []() {return q.empty() == false; });
		// 1 ���� ���
		// 2 ���� Ȯ��, �����ϸ� ���������� �̾ ����
		// �������� ������ lock�� Ǯ���ְ� ��� ����

		
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
	// Ŀ�� ������Ʈ
	// Usage Count
	// Signal(�Ķ���,true), Non-Signal(������,false)

	handle = ::CreateEvent(NULL/*���ȼӼ�*/, FALSE /*�ڵ����� signal �ʱ�ȭ*/, FALSE, NULL);
	thread t1(Producer);
	thread t2(Consumer);

	t1.join();
	t2.join();

	::CloseHandle(handle);
}