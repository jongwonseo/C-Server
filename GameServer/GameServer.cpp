#include "pch.h"
#include <iostream>
#include "CorePch.h"

#include <thread>

void HelloThread()
{
	for(auto i=0;i<1;i++)
		cout << "Hello Thread" << endl;
}

void HelloThread2(int32 num)
{
	for (auto i = 0; i < 1; i++)
		cout << num << endl;
}

int main()
{
	vector<std::thread> v;

	//std::thread t;
	//t = std::thread(HelloThread);

	//std::thread tt;
	//tt = std::thread(HelloThread2, 10);

	for (int32 i = 0; i < 10; i++)
	{
		v.push_back(std::thread(HelloThread2, i));
	}

	cout << "Hello Main" << endl;
	
	for (auto i = 0; i < v.size(); i++)
	{
		if (v[i].joinable())
			v[i].join();
	}

	//int32 count = t.hardware_concurrency(); // CPU코어 개수
	
	//auto id = t.get_id(); // 쓰레드 아이디 
	
	//t.detach(); // main쓰레드와 thread객체를 분리(데몬 프로세스), 만든 쓰레드의 정보 추출이 힘듬
	
	//if (t.joinable()) // 쓰레드 선언과 구현(실행)을 분리했을때 사용
	//	t.join(); // 쓰레드가 끝날떄까지 main쓰레드가 영영 기다려줌
}