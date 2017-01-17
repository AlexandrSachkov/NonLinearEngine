#pragma once

namespace NLE
{
	namespace DATA
	{
		class ISharedEntity
		{
		public:
			virtual void sync() = 0;
		};
	}
}
