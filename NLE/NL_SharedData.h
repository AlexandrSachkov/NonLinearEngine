#ifndef NL_SHARED_DATA_H_
#define NL_SHARED_DATA_H_

namespace NLE
{
	class SharedData
	{
	public:
		SharedData()
		{
			inputProcessorTime = 0;
			renderingEngineTime = 0;
			uiManagerTime = 0;
			scriptingEngineTime = 0;
		}

		~SharedData()
		{
		}

		double inputProcessorTime;
		double renderingEngineTime;
		double uiManagerTime;
		double scriptingEngineTime;
	};
}

#endif