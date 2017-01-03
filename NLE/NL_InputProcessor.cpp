#include "NL_InputProcessor.h"
#include "NL_InputEvents.h"
#include "NL_Globals.h"
#include "NL_ThreadLocal.h"
#include "NL_SystemServices.h"
#include "NL_IDataManager.h"
#include "NL_EngineServices.h"
#include "NL_SharedData.h"

#include <assert.h>
#include <vector>

namespace NLE
{
	namespace INPUT
	{
		InputProcessor::InputProcessor(EngineServices& eServices) :
			_eServices(eServices)
		{
			_enableTextInput.fetch_and_store(false);
			_enableInputProcessing.fetch_and_store(true);
		}

		InputProcessor::~InputProcessor()
		{

		}

		bool InputProcessor::initialize()
		{
			return true;
		}

		void InputProcessor::update(SystemServices& sServices, double deltaT)
		{
			DATA::SharedData& data = _eServices.data->getData();

			NLE::TLS::PerformanceTimer::reference timer = NLE::TLS::performanceTimer.local();
			timer.deltaT();

			INPUT::Event event;
			while (GLOBAL_EVENT_QUEUE->pop(event))
			{
				switch (event.eventType)
				{
				case EVENT_TYPE::EVENT_KEY:
					data.keysPressed.set(
						event.eventData.keyEvent.key,
						event.eventData.keyEvent.action == ACTION::ACTION_PRESS ? true : false
						);
					data.keyModsPressed.set(
						event.eventData.keyEvent.mods,
						event.eventData.keyEvent.action == ACTION::ACTION_PRESS ? true : false
						);

					for (int i = 0; i < _keyAndCharCallbacks.size(); ++i)
					{
						_keyAndCharCallbacks[i](event);
					}

					onKeyEvent(sServices, event);
					break;

				case EVENT_TYPE::EVENT_MOUSE_BUTTON:
					data.mouseButtonPressed.set(
						event.eventData.mouseButtonEvent.button,
						event.eventData.mouseButtonEvent.action == ACTION::ACTION_PRESS ? true : false
						);
					onMouseButtonEvent(event);
					break;

				case EVENT_TYPE::EVENT_CURSOR_POSITION:
					data.mouseCursorPosition.set({
						event.eventData.cursorPositionEvent.xPos,
						event.eventData.cursorPositionEvent.yPos
					});
					onCursorPositionChange(event);
					break;

				case EVENT_TYPE::EVENT_SCROLL:
					data.scrollOffset.set({
						event.eventData.scrollEvent.xOffset,
						event.eventData.scrollEvent.yOffset
					});
					onScrollEvent(event);
					break;

				case EVENT_TYPE::EVENT_CHAR:
					for (int i = 0; i < _keyAndCharCallbacks.size(); ++i)
					{
						_keyAndCharCallbacks[i](event);
					}
					break;

				case EVENT_TYPE::EVENT_WINDOW_CLOSE:
				{
					sServices.game->quitGame();
				}
				break;
				default:
					break;
				}
			}

			data.sysExecutionTimes.set(INPUT_PROCESSOR, timer.deltaT());
		}

		void InputProcessor::attachKeyAndCharCallback(std::function<void(INPUT::Event)> callback)
		{
			_keyAndCharCallbacks.push_back(callback);
		}

		void InputProcessor::queueEvent(INPUT::Event& event)
		{
			if (!_enableInputProcessing)
				return;

			// Ignore repeated events
			if (event.eventType == EVENT_KEY && event.eventData.keyEvent.action == ACTION_REPEAT)
				return;

			if (event.eventType == EVENT_MOUSE_BUTTON && event.eventData.mouseButtonEvent.action == ACTION_REPEAT)
				return;

			GLOBAL_EVENT_QUEUE->push(event);
		}

		void InputProcessor::enableInputProcessing(bool enable)
		{
			_enableInputProcessing.fetch_and_store(enable);
		}

		void InputProcessor::onKeyEvent(SystemServices& sServices, Event& event)
		{
			
		}

		void InputProcessor::onMouseButtonEvent(Event& event)
		{

		}

		void InputProcessor::onCursorPositionChange(Event& event)
		{

		}

		void InputProcessor::onScrollEvent(Event& event)
		{

		}
	}
}
