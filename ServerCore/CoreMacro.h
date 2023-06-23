#pragma once

#define  OUT

#define USE_LOCK				USE_MANY_LOCK(1);
#define USE_MANY_LOCK(count)	Lock _lock[count];
#define READ_LOCK				READ_LOCK_IDX(0);
#define READ_LOCK_IDX(idx)		ReadLockGuard readLockGuard_##idx(_locks[idx]); // d_##idx == d_1
#define WRITE_LOCK_IDX(idx)		WriteLockGuard writeLockGuard_##idx(_locks[idx]);
#define WRITE_LOCK				WRITE_LOCK_IDX(0);

#define CRASH(cause)					\
{										\
	uint32* crash = nullptr;			\
	__analysis_assume(crash != nullptr)	\
	*crash = 0xDEADBEEF;				\
}

#define ASSERT_CRASH(expr)				\
{										\
	if (!(expr))						\
	{									\
		CRASH("ASSERT_CRASH");			\
		__analysis_assume(expr);		\
	}									\
}