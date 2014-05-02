#include "stdafx.h"
#include "RenderingDevice\NLREForwardRT.h"

NLREForwardRT::NLREForwardRT(NLRERenderingDevice* renderingDevice)
{
	_renderingDevice = renderingDevice;

	_backBufferRenderTargetView = NULL;
	_noBlendState = NULL;
	_blendState = NULL;
	_depthStencilView = NULL;
	_inputLayout = NULL;
	_backFaceCull = NULL;
	_frontFaceCull = NULL;
	_textureSamplerState = NULL;
	
	
	if (!initialize())
	{
		NLRE_Log::err(NLRE_Log::CRITICAL, "ForwardRT failed to initialize");
		throw std::exception("ForwardRT failed to initialize");
	}
	
}

bool NLREForwardRT::initialize()
{
	if (!_renderingDevice->createBackBufferRenderTargetView(_backBufferRenderTargetView)) return false;
	if (!_renderingDevice->createBlendStates(false, false, 1, false, _noBlendState)) return false;
	if (!_renderingDevice->createBlendStates(true, false, 1, false, _blendState)) return false;
	if (!_renderingDevice->createDepthStencilView(_depthStencilView)) return false;
	if (!_renderingDevice->loadVertexShader(L"Shaders\\Forward_PosText_VS.cso", _vertexShader)) return false;
	if (!_renderingDevice->createInputLayout(NLREInputLayoutDescriptions::forwardPosText, _vertexShader, _inputLayout)) return false;
	if (!_renderingDevice->createRasterizerState(NLRE_CULL_BACK, NLRE_FILL_SOLID, _backFaceCull)) return false;
	if (!_renderingDevice->createRasterizerState(NLRE_CULL_FRONT, NLRE_FILL_SOLID, _frontFaceCull)) return false;
	if (!_renderingDevice->createTextureSamplerState(_textureSamplerState)) return false;
	if (!_renderingDevice->loadPixelShader(L"Shaders\\Forward_PosText_PS.cso", _pixelShader)) return false;
	
	_renderingDevice->setRenderTargets(1, _backBufferRenderTargetView, _depthStencilView);
	_renderingDevice->setVertexShader(_vertexShader);
	_renderingDevice->setPixelShader(_pixelShader);
	_renderingDevice->setInputLayout(_inputLayout);
	_renderingDevice->setPrimitiveTopology(NLRE_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	_renderingDevice->setViewPort();

	_renderingDevice->PSSetTextureSamplerState(0, 1, _textureSamplerState);
	_renderingDevice->setRasterizerState(_backFaceCull);
	
	return true;
}

NLREForwardRT::NLREForwardRT(const NLREForwardRT& other)
{
}

NLREForwardRT::~NLREForwardRT()
{
	if (_backBufferRenderTargetView) _backBufferRenderTargetView->Release();
	if (_noBlendState) _noBlendState->Release();
	if (_blendState) _blendState->Release();
	if (_depthStencilView) _depthStencilView->Release();
	if (_inputLayout) _inputLayout->Release();
	if (_backFaceCull) _backFaceCull->Release();
	if (_frontFaceCull) _frontFaceCull->Release();
	if (_textureSamplerState) _textureSamplerState->Release();
}

void NLREForwardRT::render(NLRE_Buffer vertexBuff, NLRE_Buffer indexBuff, NLRE_Buffer constBuff, NLRE_APIShaderResourceView* texture)
{
	float bgColor[4] = { 0.0f, 0.0f, 0.0f, 0.0f};
	_renderingDevice->clearRenderTargetView(_backBufferRenderTargetView, bgColor);
	_renderingDevice->clearDepthStencilView(_depthStencilView);

	float blendFactor[] = { 0.75f, 0.75f, 0.75f, 1.0f };
	//_renderingDevice->setBlendState(_noBlendState, 0);

	//	======= for every opaque object ========
	//set vertex buffer
	//set index buffer
	//update constant buffer
	//set texture resouce
	//draw object
	_renderingDevice->setVertexBuffer(vertexBuff, 0);
	_renderingDevice->setIndexBuffer(indexBuff);
	_renderingDevice->VSSetConstantBuffer(0, 1, constBuff);
	_renderingDevice->PSSetShaderResources(0, 1, texture);

	//	======= for transparant objects ========
	//_renderingDevice->setBlendState(_blendState, blendFactor);


	// ======== for every transparent object =======
	//_renderingDevice->setRasterizerState(_frontFaceCull);
	//set vertex buffer
	//set index buffer
	//update constant buffer
	//set texture resouce
	//draw object
	//_renderingDevice->setRasterizerState(_backFaceCull);
	//draw object
	_renderingDevice->drawIndexed(indexBuff);
	_renderingDevice->display();
}

