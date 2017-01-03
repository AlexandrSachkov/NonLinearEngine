#ifndef NL_INPUT_PROCESSOR_H_
#define NL_INPUT_PROCESSOR_H_

#include "NL_IInputProcessor.h"

#include "tbb\atomic.h"
#include "NL_Atomic.h"
#include <vector>

namespace NLE
{
	class EngineServices;
	namespace INPUT
	{
		class InputProcessor : public IInputProcessor
		{
		public:
			InputProcessor(EngineServices& eServices);
			~InputProcessor();
			bool initialize();

			void update(SystemServices& sServices, double deltaT);

			void queueEvent(INPUT::Event& event);
			void enableInputProcessing(bool enable);
			void attachKeyAndCharCallback(std::function<void(INPUT::Event)> callback);

		private:
			void onKeyEvent(SystemServices& sServices, Event& event);
			void onMouseButtonEvent(Event& event);
			void onCursorPositionChange(Event& event);
			void onScrollEvent(Event& event);

			EngineServices& _eServices;
			tbb::atomic<bool> _enableTextInput;
			tbb::atomic<bool> _enableInputProcessing;
			std::vector<std::function<void(INPUT::Event)>> _keyAndCharCallbacks;
		};
	}
}

#endif