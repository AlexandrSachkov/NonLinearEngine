#ifndef DATA_H_
#define DATA_H_

class Data{
public:
	Data()
	{
		_size = 1000;
		_data = new double[_size];
	}
	 
	~Data()
	{
		delete[] _data;
	}

	Data& operator=(const Data& other)
	{
		if (this == &other)
		{
			return *this;
		}
		for (int i = 0; i < _size; ++i)
		{
			_data[i] = other._data[i];
		}

		return *this;
	}

private:
	double* _data;
	int _size;
};

#endif