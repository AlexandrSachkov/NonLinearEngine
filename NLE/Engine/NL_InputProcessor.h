#ifndef NL_INPUT_PROCESSOR_H_
#define NL_INPUT_PROCESSOR_H_

#include "NLCore\NL_System.h"
#include "NL_IInputProcessor.h"
#include "NLCore\NL_SContainer.h"

#include "tbb\concurrent_queue.h"
#include "tbb\atomic.h"

namespace NLE
{
	namespace Core
	{
		class IEngine;
		class ISystem;
	}
	namespace INPUT
	{
		class InputProcessor : public Core::System, public IInputProcessor
		{
		public:
			InputProcessor();
			~InputProcessor();

			bool initialize(Core::IEngine& engine);
			void release();

			bool initialized();

			std::function<void()> const& getExecutionProcedure();
			Core::ISystem& getInterface();

			void attachPollEvents(void(*pollEvents)(void));
			void processEvent(INPUT::Event& event);
			void enableTextInput(bool enable);

		private:
			void onKeyEvent(Event& event);
			void onMouseButtonEvent(Event& event);
			void onCursorPositionChange(Event& event);
			void onScrollEvent(Event& event);

			bool _initialized;
			std::function<void()> _procedure;
			void(*_pollEvents)(void);

			tbb::concurrent_queue<INPUT::Event> _events;
			tbb::atomic<bool> _enableTextInput;

			NLE::Core::Data::SContainer<char>* _cameraCommands;
			NLE::Core::Data::SContainer<double>* _cursorCoords;
			NLE::Core::Data::SContainer<double>* _scrollOffset;
		};
	}
}

#endif