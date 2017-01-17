#pragma once

#include <malloc.h>

namespace NLE
{
	template <typename T>
	static T* alloc(size_t alignment)
	{
		return (T*)_aligned_malloc(sizeof(T), alignment);
	}

	static void free(void* ptr)
	{
		_aligned_free(ptr);
	}
}
