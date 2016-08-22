#include "NL_InputProcessor.h"
#include "NL_InputEvents.h"
#include "NL_Globals.h"
#include "NL_ThreadLocal.h"
#include "NL_SystemServices.h"
#include "NL_IDataManager.h"
#include "NL_EngineServices.h"
#include "NL_SharedData.h"

#include <assert.h>

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

		void InputProcessor::update(SystemServices* sServices, double deltaT)
		{
			if (!_enableInputProcessing)
				return;

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
						event.eventData.keyEvent.action == ACTION::ACTION_PRESS ? 1 : 0
						);
					data.keyModsPressed.set(
						event.eventData.keyEvent.mods,
						event.eventData.keyEvent.action == ACTION::ACTION_PRESS ? 1 : 0
						);

					onKeyEvent(sServices, event);
					break;

				case EVENT_TYPE::EVENT_MOUSE_BUTTON:
					data.mouseButtonPressed.set(
						event.eventData.mouseButtonEvent.button,
						event.eventData.mouseButtonEvent.action == ACTION::ACTION_PRESS ? 1 : 0
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
					data.typedCharacter.set(event.eventData.charEvent.code);
					break;

				case EVENT_TYPE::EVENT_WINDOW_CLOSE:
				{
					GAME::COMMAND::Data data;
					sServices->game->queueCommand(GAME::COMMAND::QUIT_GAME, data);
				}
				break;
				default:
					break;
				}
			}

			data.sysExecutionTimes.set(INPUT_PROCESSOR, timer.deltaT());
		}

		void InputProcessor::queueEvent(INPUT::Event& event)
		{
			// Ignore repeated events
			if (event.eventType == EVENT_KEY && event.eventData.keyEvent.action == ACTION_REPEAT)
				return;

			if (event.eventType == EVENT_MOUSE_BUTTON && event.eventData.mouseButtonEvent.action == ACTION_REPEAT)
				return;

			// Ignore text input events when text input is disabled
			if (event.eventType == EVENT_CHAR && !_enableTextInput)
				return;

			GLOBAL_EVENT_QUEUE->push(event);
		}

		void InputProcessor::enableTextInput(bool enable)
		{
			_enableTextInput.fetch_and_store(enable);
		}

		void InputProcessor::enableInputProcessing(bool enable)
		{
			_enableInputProcessing.fetch_and_store(enable);
		}

		void InputProcessor::onKeyEvent(SystemServices* sServices, Event& event)
		{
			switch (event.eventData.keyEvent.key)
			{
			case KEY::KEY_ESCAPE:
			{
				GAME::COMMAND::Data data;
				sServices->game->queueCommand(GAME::COMMAND::QUIT_GAME, data);
			}
			break;

			case KEY::KEY_F12:		//for testing purposes
			{
				GAME::COMMAND::Data data;
				sServices->game->queueCommand(GAME::COMMAND::RESTART_GAME, data);
			}
			break;

			default:
				break;
			}
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
