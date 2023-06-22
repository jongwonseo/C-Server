#include "pch.h"
#include <iostream>
#include "CorePch.h"
#include <mutex>

mutex m;
vector<int32> v;
// ���ʹ� �뷮�� ������ �ٸ� �ּҿ� ��ū ���͸� ����� ������ �����ϰ� ���� ���ʹ� ������
// �� �������� ������ ���͸� �����ϴϱ� ������ ��
// reserve�� �̿��ؼ� ���ʿ� �˳��ϰ� Ȯ��

template <typename T>
class LockGuard
{
public:
	LockGuard(T& m) {
		_mutex = &m;
		_mutex->lock();
	}

	~LockGuard()
	{
		_mutex->unlock();
	}

private:
	T* _mutex;

};

void Push()
{
	for (int32 i =0; i < 10'000; i++)
	{
		LockGuard<std::mutex> lockGuard(m);
		v.push_back(i);

		if (i == 5000) break;

	}
}
//void Push()
//{
//	for (int32 i = 0; i < 10'000; i++)
//	{
//		m.lock();
//		v.push_back(i);
//		m.unlock();
//	}
//}

int main()
{
	//v.reserve(20'000); // �Ϻ��� �ذ���X, �������� ��� ���ɼ� ����

	std::thread t1(Push);
	std::thread t2(Push);

	t1.join();
	t2.join();

	cout << v.size() << endl;
}