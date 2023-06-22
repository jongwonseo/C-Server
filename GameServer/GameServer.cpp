#include "pch.h"
#include <iostream>
#include "CorePch.h"


atomic<bool> ready;
int32 value;

void Producer()
{
	value = 0;
	ready.store(true, memory_order::memory_order_seq_cst);
	///// 절취선 ////
	// 위에서는 바껴도 됨
	// value = 0 이 못옴
}

void Consumer()
{
	///// 절취선 ////
	while (ready.load(memory_order::memory_order_seq_cst) == false);

	cout << value << endl;
}

int main()
{
	ready = false;
	value = 0;
	thread  t1(Producer);
	thread t2(Consumer);
	t1.join();
	t2.join();

}

//int main()
//{
//	atomic<bool> flag = false;
//
//	// flag = true; // store()로 오퍼레이터변환됨
//	flag.store(true, memory_order::memory_order_seq_cst);
//
//	bool val = flag.load(memory_order::memory_order_seq_cst);
//
//
//
//	// 이전 flag 값을 prev에 넣고, flag값을 수정
//	{
//		bool prev = flag.exchange(true);
//	/*	bool prev = flag;
//		flag = true;
//	*/
//	}
//
//	// CAS 조건부 수정
//	{
//		bool expected = false;
//		bool desired = true;
//
//		flag.compare_exchange_strong(expected, desired);
//		
//		// 가짜실패 Spurious Failure시 실행X
//		//flag.compare_exchange_weak(expected, desired);
//
//	}
//
//}

/*
메모리 정책
1. Sequentially Consistent(seq_cst) (엄격, 컴파일러 최적화여지 적음)
- 가시성 해결, 코드 재배치 해결

2. Acquire-Release(acquire, release, (acq_rel) (consume))
- producer(release), consumer(acquire)로 짝을 맞춰줌
-  release명령 이전의 명령들이, 해당 명령이후로 재배치 되는 것을 금지
- acquire로 같은 변수를 읽는 쓰레드가 있다면  release이전의 명령들이 acquire하는 순간에 관찰가능(가시성 보장)

3. Relaxed(relaxed) (자유로움)
- 

*/

// 인텔, amd는 자체적으로  seq_cst씀
