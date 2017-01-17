#pragma once

#include "tbb\spin_mutex.h"

namespace NLE
{
	template<typename T>
	class Atomic
	{
	public:
		Atomic()
		{
		}

		Atomic(T data) : _data(data)
		{
		}

		T& acquire()
		{
			_lock.lock();
			return _data;
		}

		void release()
		{
			_lock.unlock();
		}

		T get()
		{
			return _data;
		}

		void set(T data)
		{
			_lock.lock();
			_data = data;
			_lock.unlock();
		}


	private:
		T _data;
		tbb::spin_mutex _lock;
	};
}
