#include "NL_Octree.h"

namespace NLE
{
	Octree::Octree(glm::vec3 location, uint_fast32_t sideLength, uint_fast32_t currentLevel) :
		_location(location),
		_sideLength(sideLength),
		_currentLevel(currentLevel)
	{
		_children = nullptr;
	}

	Octree::~Octree()
	{
		if (_children)
			delete _children;
	}


}