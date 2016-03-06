#ifndef NL_INPUT_PROCESSOR_H_
#define NL_INPUT_PROCESSOR_H_

#include "NL_IInputProcessor.h"
#include "NL_ISystem.h"
#include "NL_EngineServices.h"

#include "tbb\atomic.h"
#include "NL_Atomic.h"

namespace NLE
{
	enum ExecStatus 
	{
		CONTINUE,
		TERMINATE,
		RESTART
	};

	namespace INPUT
	{
		class InputProcessor : public IInputProcessor, public ISystem
		{
		public:
			InputProcessor(EngineServices& eServices);
			~InputProcessor();
			bool initialize();

			void update(SystemServices& sServices, DataManager& data, double deltaT);
			ExecStatus getExecutionStatus();
			void queueEvent(INPUT::Event& event);
			void enableTextInput(bool enable);
			void enableInputProcessing(bool enable);

		private:
			ExecStatus _execStatus;
			void onKeyEvent(Event& event);
			void onMouseButtonEvent(Event& event);
			void onCursorPositionChange(Event& event);
			void onScrollEvent(Event& event);

			EngineServices& _eServices;
			tbb::atomic<bool> _enableTextInput;
			tbb::atomic<bool> _enableInputProcessing;
		};
	}
}

#endif