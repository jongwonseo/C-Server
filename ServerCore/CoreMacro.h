#pragma once

// Lock


// Memory
#ifdef _DEBUG
#define xalloc(size)	BaseAllocator::Alloc(size)
#define xrelease(ptr)	BaseAllocator::Release(ptr)
#else
#define xalloc(size)	BaseAllocator::Alloc(size)
#define xrelease(ptr)	BaseAllocator::Alloc(size)
#endif



// Crach
#define CRASH(cause)							\
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