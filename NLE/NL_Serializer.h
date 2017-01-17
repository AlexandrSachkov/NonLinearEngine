#pragma once

#include <vector>

namespace NLE
{
	namespace SERIALIZATION
	{
		template<class T>
		class Serializer
		{
		public:
			Serializer() {}

			template <class OT>
			std::vector<char>* serialize(OT* obj)
			{
				return static_cast<T*>(this)->serialize<OT>(obj);
			}

			template <class OT>
			OT* deserialize(std::vector<char>* data)
			{
				return static_cast<T*>(this)->deserialize<OT>(data);
			}
		};
	}
}