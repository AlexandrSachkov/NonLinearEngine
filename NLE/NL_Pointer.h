#pragma once

namespace NLE
{
	class RefCounter
	{
	public:
		RefCounter() : _numRefs(0)
		{
		}

		void addRef()
		{
			++_numRefs;
		}

		unsigned int release()
		{
			return --_numRefs;
		}

	private:
		unsigned int _numRefs;
	};

	template<typename T>
	class SharedPtr
	{
	public:
		SharedPtr(T* data = nullptr) : _data(data)
		{
			_refCounter = new RefCounter();
			_refCounter->addRef();
		}

		SharedPtr(const SharedPtr<T>& other) : 
			_data(other._data), _refCounter(other._refCounter)
		{
			_refCounter->addRef();
		}

		~SharedPtr()
		{
			release();
		}

		T& operator* ()
		{
			return *_data;
		}

		T* operator-> ()
		{
			return _data;
		}

		explicit operator bool()
		{
			return _data;
		}

		SharedPtr<T>& operator=(const SharedPtr<T>& other)
		{
			if (this != &other)
			{
				release();

				_data = other._data;
				_refCounter = other._refCounter;
				_refCounter->addRef();
			}
			return *this;
		}

	private:
		void release()
		{
			if (_refCounter->release() == 0)
			{
				delete _data;
				delete _refCounter;
			}
		}


		T* _data;
		RefCounter* _refCounter;
	};

	template<typename T>
	class WeakPtr
	{
	public:
		WeakPtr(T* ptr = nullptr) : _data(ptr){}
		WeakPtr(const WeakPtr<T>& other) : _data(other._data) {}
		~WeakPtr() {}

		T& operator* ()
		{
			return *_data;
		}

		T* operator-> ()
		{
			return _data;
		}

		explicit operator bool()
		{
			return _data;
		}
		
		WeakPtr<T>& operator=(const WeakPtr<T>& other)
		{
			if (this != &other)
			{
				_data = other._data;
			}
			return *this;
		}

	private:
		T* _data;
	};
}