#include "pch.h"
#include <iostream>
#include "CorePch.h"

thread_local int32 LThreadId = 0;

void ThreadMain(int32 threadId)
{
	LThreadId = threadId;

	while (true)
	{
		cout << "Hi " << LThreadId << endl;
		this_thread::sleep_for(1s);
	}
}



template<typename T>
void add(T a) {
}

int main()
{
	vector<thread> threads;

	for (int32 i = 0; i < 10; i++)
	{
		int32 threadId = i + 1;
		threads.push_back(thread(ThreadMain, threadId));

	}

	for (thread& t : threads)
		t.join();
	

}
