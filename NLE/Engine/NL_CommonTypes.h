#ifndef NL_COMMON_TYPES_H_
#define NL_COMMON_TYPES_H_

#include <cstdint>

namespace NLE
{
	struct Size2D
	{
		Size2D() : width(0), height(0) {}
		Size2D(int_fast32_t width, int_fast32_t height) : width(width), height(height) {}

		uint_fast32_t width;
		uint_fast32_t height;
	};

	struct Position2D
	{
		Position2D() : x(0), y(0) {}
		Position2D(int_fast32_t x, int_fast32_t y) : x(x), y(y) {}

		int_fast32_t x;
		int_fast32_t y;
	};

	struct Offset2D
	{
		Offset2D() : x(0), y(0) {}
		Offset2D(int_fast32_t x, int_fast32_t y) : x(x), y(y) {}

		int_fast32_t x;
		int_fast32_t y;
	};
}

#endif