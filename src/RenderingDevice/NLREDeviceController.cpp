#include "stdafx.h"
#include "RenderingDevice\NLREDeviceController.h"

NLREDeviceController::NLREDeviceController(HWND hwndVal, int widthVal, int heightVal, NLRE_RENDERING_TECHNIQUE_ID techniqueId)
: _renderingDevice(hwndVal, widthVal, heightVal)
{
	_renderingTechniqueId = techniqueId;
	setRenderingTechnique(techniqueId);
	if (!initialize())
	{
		NLRE_Log::err(NLRE_Log::CRITICAL, "Device controller failed to initialize");
		throw new std::exception("Device controller failed to initialize");
	}
}

bool NLREDeviceController::initialize()
{
	return true;
}

NLRERenderingDevice* NLREDeviceController::getRenderingDevice()
{
	return &_renderingDevice;
}

bool NLREDeviceController::setRenderingTechnique(NLRE_RENDERING_TECHNIQUE_ID techniqueId)
{
	try
	{
		switch (techniqueId)
		{
		case NLRE_FORWARD_RT:
			_renderingTechnique = new NLREForwardRT(&_renderingDevice);
			break;
		}
	}
	catch (std::exception& e)
	{
		return false;
	}
	return true;
}

NLRE_RENDERING_TECHNIQUE_ID NLREDeviceController::getCurrentRenderingTechniqueId()
{
	return _renderingTechniqueId;
}

void NLREDeviceController::render()
{
	_renderingTechnique->render();
}