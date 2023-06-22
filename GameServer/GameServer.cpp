#include "pch.h"
#include <iostream>
#include "CorePch.h"


atomic<bool> ready;
int32 value;

void Producer()
{
	value = 0;
	ready.store(true, memory_order::memory_order_seq_cst);
	///// ���뼱 ////
	// �������� �ٲ��� ��
	// value = 0 �� ����
}

void Consumer()
{
	///// ���뼱 ////
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
//	// flag = true; // store()�� ���۷����ͺ�ȯ��
//	flag.store(true, memory_order::memory_order_seq_cst);
//
//	bool val = flag.load(memory_order::memory_order_seq_cst);
//
//
//
//	// ���� flag ���� prev�� �ְ�, flag���� ����
//	{
//		bool prev = flag.exchange(true);
//	/*	bool prev = flag;
//		flag = true;
//	*/
//	}
//
//	// CAS ���Ǻ� ����
//	{
//		bool expected = false;
//		bool desired = true;
//
//		flag.compare_exchange_strong(expected, desired);
//		
//		// ��¥���� Spurious Failure�� ����X
//		//flag.compare_exchange_weak(expected, desired);
//
//	}
//
//}

/*
�޸� ��å
1. Sequentially Consistent(seq_cst) (����, �����Ϸ� ����ȭ���� ����)
- ���ü� �ذ�, �ڵ� ���ġ �ذ�

2. Acquire-Release(acquire, release, (acq_rel) (consume))
- producer(release), consumer(acquire)�� ¦�� ������
-  release��� ������ ��ɵ���, �ش� ������ķ� ���ġ �Ǵ� ���� ����
- acquire�� ���� ������ �д� �����尡 �ִٸ�  release������ ��ɵ��� acquire�ϴ� ������ ��������(���ü� ����)

3. Relaxed(relaxed) (�����ο�)
- 

*/

// ����, amd�� ��ü������  seq_cst��
