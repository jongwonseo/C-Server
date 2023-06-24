#include "pch.h"
#include "Allocator.h"

void* BaseAllocator::Alloc(int32 size)
{
	return std::malloc(size);
}

void BaseAllocator::Release(void* ptr)
{
	return ::free(ptr);
}

