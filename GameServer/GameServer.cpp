#include "pch.h"
#include <iostream>
#include "CorePch.h"
#include "CoreMacro.h"
#include "ThreadManager.h"
#include "refCounting.h"

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
}