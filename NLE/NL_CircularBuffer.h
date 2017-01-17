#pragma once

#include <vector>

namespace NLE
{
	template<typename T>
	class CircularBuffer
	{
	public:
		CircularBuffer(size_t size) :
			_buffer(size),
			_index(0),
			_start(0),
			_numElements(0)
		{}
		~CircularBuffer() {}

		void push(T val)
		{
			if (_index == _start && _numElements > 0)
				_start = (_start + 1) % _buffer.size();

			_buffer[_index] = val;
			_index = (_index + 1) % _buffer.size();

			if(_numElements < _buffer.size())
				++_numElements;
		}

		size_t size()
		{
			return _numElements;
		}

		size_t capacity()
		{
			return _buffer.size();
		}

		T& operator [](unsigned int i) { 
			return _buffer[(_start + i) % _buffer.size()];
		}
	private:
		unsigned int _index;
		unsigned int _start;
		size_t _numElements;
		std::vector<T> _buffer;
	};
}