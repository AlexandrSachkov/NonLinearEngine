#ifndef NLRE_DEVICE_CONTROLLER_
#define NLRE_DEVICE_CONTROLLER_

#include "NLREForwardRT.h"

class NLREDeviceController
{
public:
	NLREDeviceController(HWND hwndVal, int widthVal, int heightVal, NLRE_RENDERING_TECHNIQUE_ID techniqueId);
	NLREDeviceController(const NLREDeviceController&);
	~NLREDeviceController();
	NLRERenderingDevice* getRenderingDevice();
	bool setRenderingTechnique(NLRE_RENDERING_TECHNIQUE_ID techniqueId);
	NLRE_RENDERING_TECHNIQUE_ID getCurrentRenderingTechniqueId();
	void render(NLRE_Buffer vertexBuff, NLRE_Buffer indexBuff, NLRE_Buffer constBuff, NLRE_APIShaderResourceView* texture);

NLRERenderingTechnique* _renderingTechnique;
private:
	bool initialize();
	NLRE_RENDERING_TECHNIQUE_ID _renderingTechniqueId;
	NLRERenderingDevice _renderingDevice;
	
};
#endif