#include "stdafx.h"
#include "RenderingDevice\NLREDeviceController.h"

NLREDeviceController::NLREDeviceController(HWND hwndVal, int widthVal, int heightVal, NLRE_RENDERING_TECHNIQUE_ID techniqueId)
: _renderingDevice(hwndVal, widthVal, heightVal)
{
	_renderingTechniqueId = techniqueId;
	
	if (!initialize())
	{
		NLRE_Log::err(NLRE_Log::CRITICAL, "Device controller failed to initialize");
		throw std::exception("Device controller failed to initialize");
	}
}

NLREDeviceController::~NLREDeviceController()
{
	if (_renderingTechnique) delete _renderingTechnique;
}

bool NLREDeviceController::initialize()
{
	if (!setRenderingTechnique(_renderingTechniqueId)) return false;
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
		default:
			throw std::exception("Unsupported Rendering Technique.");
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

void NLREDeviceController::render(NLRE_Buffer vertexBuff, NLRE_Buffer indexBuff, NLRE_Buffer constBuff, NLRE_APIShaderResourceView* texture)
{
	_renderingTechnique->render(vertexBuff, indexBuff, constBuff, texture);
}