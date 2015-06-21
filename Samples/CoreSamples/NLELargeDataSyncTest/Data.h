#ifndef DATA_H_
#define DATA_H_

class Data{
public:
	Data() : _size(1000)
	{
	}
	 
	~Data()
	{
	}

private:
	double _data[1000];
	int _size;
};

#endif