#include "stdafx.h"
#include "NLRE.h"

NLRE::NLRE(HWND hwndVal, int widthVal, int heightVal){
	_deviceController = new NLREDeviceController(hwndVal, widthVal, heightVal, NLRE_RENDERING_TECHNIQUE_ID::NLRE_FORWARD_RT);
	_renderingDevice = _deviceController->getRenderingDevice();
	_container = new Container(_deviceController, _renderingDevice, widthVal, heightVal);
}

NLRE::~NLRE(){

}

void NLRE::render()
{
	_container->render();
}
