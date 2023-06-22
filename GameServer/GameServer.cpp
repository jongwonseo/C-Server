#include "pch.h"
#include <iostream>
#include "CorePch.h"

#include <future>

int64 Calculate()
{
	int64 sum = 0;
	for (int64 i = 0; i < 1'000'000'000; i++)
	{
		sum += i;
	}
	return sum;
}

void PromiseWorker(std::promise<string>&& promise)
{
	promise.set_value("Secret Message");
}

int main()
{
	Calculate();

	// Future(�񵿱� �Լ� ����)
	
	// deferred -> lazy evaluation
	// async -> ������ ������ ���� ����
	{
		//std::future<int64> future;
		auto future = std::async(std::launch::async, Calculate);


		/*std::future_status status = future.wait_for(1ms);
		if (status == future_status::ready)
		{
		}*/

		int64 sum = future.get();
		cout << sum << endl;
		
		/*
		class Knight
		{
		public:
			int64 GetHp() { return 100; }
		};

		Knight knight;
		auto i = std::async(std::launch::async, Knight::GetHp, knight);
		*/
	}


	// std::promise
	{
		//�̷�(std::future)�� ������� ��ȯ�غҰŶ� ���(std::promise)����
		std::promise<string> promise;
		std::future<string> future = promise.get_future();
	
		thread t(PromiseWorker, std::move(promise));
		string message = future.get();
		
		cout << message << endl;
		t.join();
	}

	// std::packaged_task
	{
		std::packaged_task<int64(void)> task(Calculate);
		std::future<int64> future = task.get_future();
 
	}
}