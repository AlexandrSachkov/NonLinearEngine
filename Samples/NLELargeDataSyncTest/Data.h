#ifndef DATA_H_
#define DATA_H_

class Data{
public:
	Data() : _size(100)
	{
	}
	 
	~Data()
	{
	}

private:
	double _data[100];
	int _size;
};

#endif