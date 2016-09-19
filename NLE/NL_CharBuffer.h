#ifndef NL_CHAR_BUFFER_H_
#define NL_CHAR_BUFFER_H_

#include <string>
#include <vector>
#include <assert.h>

namespace NLE
{
	class CharBuffer
	{
	public:
		CharBuffer(size_t size) :
			_data(size)
		{
			memset(&_data[0], 0, _data.size());
		}

		CharBuffer& operator=(CharBuffer& other)
		{
			_data = other._data;
		}

		~CharBuffer()
		{
		}
		
		bool isEmpty()
		{
			return _data[0] == '\0' ? true : false;
		}

		size_t getSize()
		{
			return _data.size();
		}

		void setText(std::string text)
		{
			assert(text.size() <= _data.size());
			memset(&_data[0], 0, _data.size());
			std::copy(text.begin(), text.end(), _data.begin());
		}

		std::string getText()
		{
			std::string text(&_data[0]);
			return text;
		}

		char& operator[](int i)
		{
			return _data[i];
		}

	private:
		std::vector<char> _data;
	};
}

#endif