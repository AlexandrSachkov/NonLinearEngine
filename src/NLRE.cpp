#include "stdafx.h"
#include "NLRE.h"

NLRE::NLRE(HWND hwndVal, int widthVal, int heightVal){
	_deviceController = new NLREDeviceController(hwndVal, widthVal, heightVal, NLRE_RENDERING_TECHNIQUE_ID::NLRE_FORWARD_RT);
	_renderingDevice = _deviceController->getRenderingDevice();
	_textureLoader = new NLREFreeImgTextureLoader(_renderingDevice);
	_container = new Container(_deviceController, _renderingDevice, _textureLoader, widthVal, heightVal);
	
}

NLRE::~NLRE(){

	if (_deviceController) delete _deviceController;
	if (_container) delete _container;
}

void NLRE::render()
{
	_container->render();
}
