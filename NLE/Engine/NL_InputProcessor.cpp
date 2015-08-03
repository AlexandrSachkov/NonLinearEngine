#include "NL_InputProcessor.h"
#include "NL_InputEvents.h"
#include "NLCore\NL_IEngine.h"
#include "NLCore\NL_SDistributor.h"

#include "NL_SharedContainers.h"
#include "NL_IRenderer.h"
#include "NL_Systems.h"

#include <assert.h>

namespace NLE
{
	namespace INPUT
	{
		InputProcessor::InputProcessor() :
			_initialized(false)
		{
			_enableTextInput.fetch_and_store(false);
		}

		InputProcessor::~InputProcessor()
		{

		}

		bool InputProcessor::initialize(Core::IEngine& engine)
		{
			assert(!_initialized && _pollEvents);

			_cameraCommands = &static_cast<NLE::Core::Data::SDistributor<char>*>(&engine.getSDistributor(CAMERA_COMMANDS))->buildEndpoint(SYS::SYS_INPUT_PROCESSOR);
			_cursorCoords = &static_cast<NLE::Core::Data::SDistributor<double>*>(&engine.getSDistributor(CURSOR_COORDINATES))->buildEndpoint(SYS::SYS_INPUT_PROCESSOR);
			_scrollOffset = &static_cast<NLE::Core::Data::SDistributor<double>*>(&engine.getSDistributor(SCROLL_OFFSET))->buildEndpoint(SYS::SYS_INPUT_PROCESSOR);

			_procedure = [&](){
				_pollEvents();

				if (!_events.empty())
				{
					INPUT::Event event;
					while (_events.try_pop(event))
					{
						switch (event.eventType)
						{
						case EVENT_TYPE::EVENT_KEY:
							onKeyEvent(event);
							break;
						case EVENT_TYPE::EVENT_MOUSE_BUTTON:
							onMouseButtonEvent(event);
							break;
						case EVENT_TYPE::EVENT_CURSOR_POSITION:
							onCursorPositionChange(event);
							break;
						case EVENT_TYPE::EVENT_SCROLL:
							onScrollEvent(event);
							break;
						default:
							break;
						}
					}
				}
			};

			_initialized = true;
			return _initialized;
		}

		void InputProcessor::release()
		{

		}

		bool InputProcessor::initialized()
		{
			return _initialized;
		}

		std::function<void()> const& InputProcessor::getExecutionProcedure()
		{
			return _procedure;
		}

		Core::ISystem& InputProcessor::getInterface()
		{
			return *this;
		}

		void InputProcessor::attachPollEvents(std::function<void()> const& operation)
		{
			assert(!_initialized);
			_pollEvents = operation;
		}

		void InputProcessor::processEvent(INPUT::Event& event)
		{
			// Ignore repeated events
			if (event.eventType == EVENT_KEY && event.eventData.keyEvent.action == ACTION_REPEAT)
				return;

			if(event.eventType == EVENT_MOUSE_BUTTON && event.eventData.mouseButtonEvent.action == ACTION_REPEAT)
				return;

			// Ignore text input events when text input is disabled
			if (event.eventType == EVENT_CHAR && !_enableTextInput)
				return;

			_events.push(event);
		}

		void InputProcessor::enableTextInput(bool enable)
		{
			_enableTextInput.fetch_and_store(enable);
		}

		void InputProcessor::onKeyEvent(Event& event)
		{
			// temporary hardcoded key mappings
			switch (event.eventData.keyEvent.key)
			{
			case KEY::KEY_A:
				if (event.eventData.keyEvent.action == ACTION::ACTION_PRESS)
					_cameraCommands->modify(GRAPHICS::COMMANDS::CAMERA::LEFT, 1);
				else
					_cameraCommands->modify(GRAPHICS::COMMANDS::CAMERA::LEFT, 0);
				break;
			case KEY::KEY_D:
				if (event.eventData.keyEvent.action == ACTION::ACTION_PRESS)
					_cameraCommands->modify(GRAPHICS::COMMANDS::CAMERA::RIGHT, 1);
				else
					_cameraCommands->modify(GRAPHICS::COMMANDS::CAMERA::RIGHT, 0);
				break;
			case KEY::KEY_W:
				if (event.eventData.keyEvent.action == ACTION::ACTION_PRESS)
					_cameraCommands->modify(GRAPHICS::COMMANDS::CAMERA::FORWARD, 1);
				else
					_cameraCommands->modify(GRAPHICS::COMMANDS::CAMERA::FORWARD, 0);
				break;
			case KEY::KEY_S:
				if (event.eventData.keyEvent.action == ACTION::ACTION_PRESS)
					_cameraCommands->modify(GRAPHICS::COMMANDS::CAMERA::REVERSE, 1);
				else
					_cameraCommands->modify(GRAPHICS::COMMANDS::CAMERA::REVERSE, 0);
				break;
			default:
				break;
			}
		}

		void InputProcessor::onMouseButtonEvent(Event& event)
		{
			//temporary hardcoded mouse mappings
			switch (event.eventData.mouseButtonEvent.button)
			{
			case MOUSE::MOUSE_BUTTON_LEFT:
				break;
			case MOUSE::MOUSE_BUTTON_MIDDLE:
				break;
			case MOUSE::MOUSE_BUTTON_RIGHT:
				break;
			default:
				break;
			}
		}

		void InputProcessor::onCursorPositionChange(Event& event)
		{
			_cursorCoords->modify(0, event.eventData.cursorPositionEvent.xPos);
			_cursorCoords->modify(1, event.eventData.cursorPositionEvent.yPos);
		}

		void InputProcessor::onScrollEvent(Event& event)
		{
			_scrollOffset->modify(0, event.eventData.scrollEvent.xOffset);
			_scrollOffset->modify(1, event.eventData.scrollEvent.yOffset);
		}
	}
}
