#pragma once

#include "cereal\cereal.hpp"
#include "cereal/types/unordered_map.hpp"

#include <unordered_map>

namespace NLE
{
	enum OverwriteMode
	{
		REPLACE,
		KEEP_EXISTING
	};

	template<typename K, typename V, OverwriteMode M>
	class Map
	{
	public:
		Map()
		{
		}

		Map(const Map& other)
		{
			_map = other._map;
		}

		Map& operator=(const Map& other)
		{
			_map = other._map;
			return *this;
		}

		~Map()
		{
		}

		bool insert(K key, V value)
		{
			auto iter = _map.find(key);
			if (iter != _map.end())
			{
				if (M == REPLACE)
				{
					iter->second = value;
				}
				else
				{
					return false;
				}			
			}
			else
			{
				_map.insert(std::make_pair<>(key, value));
			}			
			return true;
		}

		bool get(K key, V& value)
		{
			auto iter = _map.find(key);
			if (iter != _map.end())
			{
				value = iter->second;
				return true;
			}
			return false;
		}

		const std::unordered_map<K, V>& getData() const
		{
			return _map;
		}

		bool erase(K key)
		{
			if (_map.erase(key))
				return true;
			else
				return false;
		}

		template<class Archive>
		void save(Archive& archive) const
		{
			archive(CEREAL_NVP(_map));
		}

		template<class Archive>
		void load(Archive& archive)
		{
			archive(CEREAL_NVP(_map));
		}

	private:
		std::unordered_map<K, V> _map;
	};
}