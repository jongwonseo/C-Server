#include "pch.h"
#include <iostream>
#include "CorePch.h"
#include "CoreMacro.h"
#include "ThreadManager.h"
#include "refCounting.h"
#include "Memory.h"
#include "ObjectPool.h"

//#include "LockFreeStack.h"


DECLSPEC_ALIGN(16)
class Data
{
public:
	SLIST_ENTRY _entry;
	int64 _rand = rand() % 100;
};

SLIST_HEADER* GHeader;

class Knight {};

int main()
{
	
}