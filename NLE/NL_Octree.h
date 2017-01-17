#pragma once

#include "glm/glm.hpp"
#include "tbb/concurrent_vector.h"

#include <cstdint>

namespace NLE
{
	class Octree
	{
	public:
		Octree(glm::vec3 location, uint_fast32_t sideLength, uint_fast32_t currentLevel);
		~Octree();

	private:
		glm::vec3 _location;
		uint_fast32_t _sideLength;
		uint_fast32_t _currentLevel;
		Octree* _children;

		static const uint_fast32_t MAX_LEVEL = 8;
	};
}
