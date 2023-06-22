#include "pch.h"
#include <iostream>
#include "CorePch.h"
#include <mutex>

mutex m;
vector<int32> v;
// 벡터는 용량이 꽉차면 다른 주소에 더큰 벡터를 만들고 데이터 복사하고 현재 백터는 삭제함
// 이 과정에서 삭제된 벡터를 참조하니까 에러가 남
// reserve를 이용해서 애초에 넉넉하게 확보

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
	//v.reserve(20'000); // 완벽한 해결방안X, 같은곳에 덮어쓸 가능성 있음

	std::thread t1(Push);
	std::thread t2(Push);

	t1.join();
	t2.join();

	cout << v.size() << endl;
}