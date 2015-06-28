#ifndef NL_INPUT_PROCESSOR_H_
#define NL_INPUT_PROCESSOR_H_

#include "NLCore\NL_System.h"
#include "NL_IInputProcessor.h"

#include "tbb\concurrent_queue.h"

namespace NLE
{
	namespace Core
	{
		class IEngine;
		class ISystem;
	}
	
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

		void attachEventPollingOperation(std::function<void()> operation);
		void processEvent(INPUT::Event& event);

	private:
		bool _initialized;
		std::function<void()> _procedure;
		std::function<void()> _eventPoller;

		tbb::concurrent_queue<INPUT::Event> _events;
	};
}

#endif