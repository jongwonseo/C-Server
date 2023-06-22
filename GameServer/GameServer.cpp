#include "pch.h"
#include <iostream>
#include "CorePch.h"

#include <atomic>
#include <mutex>


class SpinLock
{
public:
	bool lock()
	{
		// CAS (Compare-And-Swap)

		bool expected = false;
		bool desired = true;

		//if (_locked == expected)
		//{
		//	expected = _locked;
		//	_locked = desired;
		//	return true;
		//}
		//else
		//{
		//	expected = _locked;
		//	return false;
		//}


		// true여야 lock흭득
		while (_locked.compare_exchange_strong(expected, desired) == false)
		{
			expected = false;
			//this_thread::sleep_for(std::chrono::milliseconds(100));
			this_thread::sleep_for(100ms); //오버로딩 되어있음
			
		}

	}

	void unlock()
	{
		_locked.store(false);
	}
private:
	atomic<bool> _locked = false;
};


int32 sum = 0;
lock_guard<mutex> m;
SpinLock spinLock;

//mutex m;

void Add()
{
	for (int32 i = 0; i < 100'000; i++)
	{
		//lock_guard<mutex> guard(m);
		spinLock.lock();
		sum++;
	}
}

void Sub()
{
	for (int32 i = 0; i < 100'000; i++)
	{
		lock_guard<SpinLock> guard(spinLock);
		sum--;
	}
}
//
int main()
{
	thread t1(Add);
	thread t2(Sub);

	t1.join();
	t2.join();

	cout << sum << endl;
}