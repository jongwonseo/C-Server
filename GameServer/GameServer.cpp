#include "pch.h"
#include <iostream>
#include "CorePch.h"
#include "CoreMacro.h"
#include "ThreadManager.h"
<<<<<<< Updated upstream
#include "refCounting.h"
=======
#include "Memory.h"
>>>>>>> Stashed changes

class Wraith;
class Missile;

using WraithRef = TSharedPtr<Wraith>;
using MissileRef = TSharedPtr<Missile>;

class Wraith : public RefCountable
{
public:
	int _hp = 150;
	int _posX = 0;
	int _posY = 0;
};

using WraithRef = TSharedPtr<Wraith>;

class Missile : public RefCountable
{
public:
	void SetTarget(WraithRef target)
	{
		_target = target;
		// 중간에 개입 가능
		//target->AddRef();

	}

	bool Update()
	{
		if (_target == nullptr)
			return true;

		int posX = _target->_posX;
		int posY = _target->_posY;

		// TODO : 쫓아간다

		if (_target->_hp == 0)
		{
			//_target->ReleaseRef();
			_target = nullptr;
			return true;
		}

		return false;
	}

<<<<<<< Updated upstream
	WraithRef _target = nullptr;
};

int main()
{
	WraithRef wraith(new Wraith());
	wraith->ReleaseRef();
	MissileRef missile(new Missile());
	missile->ReleaseRef();

	missile->SetTarget(wraith);

	// 레이스가 피격 당함
	wraith->_hp = 0;
	//delete Wraith;
	//Wraith->ReleaseRef();
	wraith = nullptr;

	while (true)
	{
		if (missile)
		{
			if (missile->Update())
			{
				//missile->ReleaseRef();
				missile = nullptr;
			}
		}
	}

	//missile->ReleaseRef();
	missile = nullptr;
	//delete missile;
=======
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
	/*
	static void* operator new(size_t size)
	{
		cout << "Knight new " << size << endl;
		void* ptr = ::malloc(size);
		return ptr;
	}

	static void operator delete(void* ptr)
	{
		cout << "Knight delete " << endl;
		::free(ptr);
	}

	static void* operator new[](size_t size)
	{
		cout << "Knight new[] " << size << endl;
		void* ptr = ::malloc(size);
		return ptr;
	}

	static 	void operator delete[](void* ptr)
	{
		cout << "Knight delete " << endl;
		::free(ptr);
	}
	*/


};

//void* operator new(size_t size)
//{
//	cout << "new " << size << endl;
//	void* ptr = ::malloc(size);
//	return ptr;
//}
//
//void operator delete(void* ptr)
//{
//	cout << "delete "<< endl;
//	::free(ptr);
//}
//
//void* operator new[](size_t size)
//{
//	cout << "new[] " << size << endl;
//	void* ptr = ::malloc(size);
//	return ptr;
//}
//
//void operator delete[](void* ptr)
//{
//	cout << "delete " << endl;
//	::free(ptr);
//}
//

int main()
{
	Knight* kinght = xnew<Knight>();

	xdelete<Knight>(kinght);

	Knight* kinght2 = xnew<Knight>(10);

	xdelete<Knight>(kinght2);
>>>>>>> Stashed changes
}