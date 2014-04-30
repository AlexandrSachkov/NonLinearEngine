#ifndef NLRE_FORWARD_RT_
#define NLRE_FORWARD_RT_

#include "RenderingDevice\NLRERenderingDevice.h"
#include "RenderingDevice\NLRERenderingTechnique.h"

class NLREForwardRT : public virtual NLRERenderingTechnique
{
public:

	NLREForwardRT(NLRERenderingDevice* renderingDevice);
	NLREForwardRT(const NLREForwardRT& other);
	~NLREForwardRT();

	void render(NLRE_Buffer vertexBuff, NLRE_Buffer indexBuff, NLRE_Buffer constBuff, NLRE_APIShaderResourceView* texture);
private:
	bool initialize();
	NLRERenderingDevice* _renderingDevice;

	//Resources and States

	NLRE_APIRenderTargetView* _backBufferRenderTargetView;
	NLRE_APIBlendState* _noBlendState;
	NLRE_APIBlendState* _blendState;
	NLRE_APIDepthStencilView* _depthStencilView;
	NLRE_VertexShader	_vertexShader;
	NLRE_APIInputLayout* _inputLayout;
	NLRE_APIRasterizerState* _backFaceCull;
	NLRE_APIRasterizerState* _frontFaceCull;
	NLRE_APISamplerState*	_textureSamplerState;
	NLRE_PixelShader _pixelShader;
	
	
};

#endif