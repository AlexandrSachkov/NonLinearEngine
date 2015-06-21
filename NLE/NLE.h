#ifndef NLE_H_
#define NLE_H_

class NLE
{
public:
	static NLE& instance()
	{
		if (!_nle)
		{
			_nle = new NLE();
		}
		return *_nle;
	};

	~NLE();

	bool initialize();
	void release();

	void run();
	void stop();

private:
	NLE();
	NLE(NLE const&) = delete;
	void operator=(NLE const&) = delete;

	static NLE* _nle;
};

#endif