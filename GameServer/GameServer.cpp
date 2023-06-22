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

	//int32 count = t.hardware_concurrency(); // CPU�ھ� ����
	
	//auto id = t.get_id(); // ������ ���̵� 
	
	//t.detach(); // main������� thread��ü�� �и�(���� ���μ���), ���� �������� ���� ������ ����
	
	//if (t.joinable()) // ������ ����� ����(����)�� �и������� ���
	//	t.join(); // �����尡 ���������� main�����尡 ���� ��ٷ���
}