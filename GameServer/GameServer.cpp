#include "pch.h"
#include <iostream>
#include "CorePch.h"
#include "CoreMacro.h"
#include "ThreadManager.h"
#include "refCounting.h"
#include "Memory.h"

class Knight 
{
public:
	Knight() {
		cout << "default" << endl;
	}
	Knight(int32 i) 
	{
		cout << "int" << endl;
	}

	~Knight()
	{
		cout << "~knight" << endl;
	}

	int _hp1 = 100;

};
class Person {};
void* operator new(size_t size)
{
	cout << "new " << size << endl;
	void* ptr = malloc(size);
	return ptr;
}

int main()
{
	Knight* knight = xnew<Knight>(100);
	xdelete(knight);
	knight->_hp1 = 10;

}